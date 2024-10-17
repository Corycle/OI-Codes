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
const int N=10005;
const int M=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Flow,Cost,cnt=1;
int h[N],A[N],B[N],a[N],b[N],num[M][M];
int dis[N],vis[N],pre[N],num1[M],num2[N];
struct edge{int to,next,flow,cost;}d[N];
void Add(int x,int y,int f,int c){
	d[++cnt]=(edge){y,h[x],f,c};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0,-c};h[y]=cnt;
}
bool SPFA(int s,int t){
	for(int i=1;i<=t;i++){dis[i]=inf;vis[i]=pre[i]=0;}
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
	Flow+=dlt;Cost+=dlt*dis[t];
}
void Edmonds_Karp(int s,int t){
	Flow=Cost=0;
	while(SPFA(s,t))Adjust(s,t);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		A[i]=a[i]=read();
		B[i]=b[i]=read();
	}
	int S=n*2+1,T=n*2+2;
	sort(A+1,A+n+1);A[0]=unique(A+1,A+n+1)-A-1;
	sort(B+1,B+n+1);B[0]=unique(B+1,B+n+1)-B-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(A+1,A+A[0]+1,a[i])-A;
		b[i]=lower_bound(B+1,B+B[0]+1,b[i])-B;
		num1[a[i]]++;num2[b[i]]++;num[a[i]][b[i]]=1;
	}
	for(int i=1;i<=A[0];i++)Add(S,i,num1[i],0);
	for(int i=1;i<=B[0];i++)Add(i+n,T,num2[i],0);
	for(int i=1;i<=A[0];i++){
		for(int j=1;j<=B[0];j++){
			Add(i,j+n,1,num[i][j]);
		}
	}
	Edmonds_Karp(S,T);
	printf("%d",Cost);
	return 0;
}