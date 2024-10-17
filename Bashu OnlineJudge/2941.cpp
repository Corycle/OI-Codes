/*====Corycle====*/
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
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
const int M=100005;
const int N=1005;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
int n,m,tot,Flow,cnt=1;ll Cost;
int A[N],B[N][2],W[N],P[N],h[N],H[N],dis[N],dep[N],vis[N];
struct edge{int to,next,flow,cost;}d[M];
void Add(int x,int y,int f,int c){
	d[++cnt]=(edge){y,h[x],f,c};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0,-c};h[y]=cnt;
}
bool SPFA(int s,int t){
	for(int i=1;i<=tot;i++){dis[i]=inf;dep[i]=-1;}
	queue<int>q;q.push(s);dis[s]=0;dep[s]=0;
	while(q.size()){
		int x=q.front();q.pop();vis[x]=0;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].flow&&dis[y]>dis[x]+d[i].cost){
				dis[y]=dis[x]+d[i].cost;dep[y]=dep[x]+1;
				if(!vis[y]){vis[y]=1;q.push(y);}
			}
		}
	}
	return dis[t]!=inf;
}
int DFS(int x,int maxx,int t){
	if(x==t||!maxx)return maxx;
	int ans=0;
	for(int &i=H[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].flow&&dis[y]==dis[x]+d[i].cost&&dep[y]==dep[x]+1){
			int dlt=DFS(y,min(d[i].flow,maxx),t);
			d[i].flow-=dlt;
			d[i^1].flow+=dlt;
			maxx-=dlt;ans+=dlt;
			if(!maxx)return ans;
		}
	}
	return ans;
}
void ZKW(int s,int t){
	Flow=Cost=0;
	while(SPFA(s,t)){
		for(int i=1;i<=tot;i++)H[i]=h[i];
		int dlt=DFS(s,inf,t);
		Flow+=dlt;Cost+=1ll*dlt*dis[t];
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	m=read();n=read();
	int S=++tot,T=++tot;
	for(int i=1;i<=n;i++){
		A[i]=++tot;
		Add(S,A[i],read(),0);
	}
	for(int i=1;i<=m;i++){
		B[i][0]=++tot;
		B[i][1]=++tot;
		Add(B[i][1],T,inf,0);
		for(int j=1;j<=n;j++){
			if(read())Add(A[j],B[i][0],inf,0);
		}
	}
	for(int i=1;i<=m;i++){
		int num=read();P[num+1]=inf;
		for(int j=1;j<=num;j++)P[j]=read();
		for(int j=1;j<=num+1;j++)W[j]=read();
		for(int j=1;j<=num+1;j++){
			Add(B[i][0],B[i][1],P[j]-P[j-1],W[j]);
		}
	}
	ZKW(S,T);
	printf("%lld",Cost);
	return 0;
}