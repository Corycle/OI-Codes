/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
int n,m,K,tot,cnt=1;
int h[N],A[N],B[N],vis[N],dis[N],pre[N],a[N][N];
struct edge{int to,next,flow,cost;}d[N*N];
void Add(int x,int y,int f,int c){
	d[++cnt]=(edge){y,h[x],f,c};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0,-c};h[y]=cnt;
}
bool SPFA(int s,int t){
	for(int i=1;i<=tot;i++){dis[i]=inf;vis[i]=pre[i]=0;}
	queue<int>q;q.push(s);dis[s]=0;
	while(q.size()){
		int x=q.front();q.pop();vis[x]=0;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].flow&&dis[y]>dis[x]+d[i].cost){
				dis[y]=dis[x]+d[i].cost;pre[y]=i;
				if(!vis[y]){vis[y]=1;q.push(y);}
			}
		}
	}
	return (dis[t]!=inf);
}
void Adjust(int s,int t){
	int dlt=inf;
	for(int i=t;i!=s;i=d[pre[i]^1].to){
		dlt=min(dlt,d[pre[i]].flow);
	}
	for(int i=t;i!=s;i=d[pre[i]^1].to){
		d[pre[i]].flow-=dlt;
		d[pre[i]^1].flow+=dlt;
	}
	Ans+=1ll*dlt*dis[t];
}
void Edmonds_Karp(int s,int t){while(SPFA(s,t))Adjust(s,t);}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read()+1;m=read();K=read();
	memset(a,0x3f,sizeof(a));
	for(int i=1;i<=n;i++){A[i]=++tot;B[i]=++tot;a[i][i]=0;}
	for(int i=1;i<=m;i++){
		int x=read()+1,y=read()+1,z=read();
		a[x][y]=a[y][x]=min(a[x][y],z);
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(k<=max(i,j))a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
			}
		}
	}
	int S=++tot,T=++tot;
	for(int i=1;i<=n;i++){
		Add(B[i],T,1,0);
		Add(S,A[i],(i==1?K:1),0);
		for(int j=i+1;j<=n;j++)Add(A[i],B[j],inf,a[i][j]);
	}
	Edmonds_Karp(S,T);
	printf("%lld",Ans);
	return 0;
}