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
const int M=4e5+5;
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
int n,K,cnt,tot,Min,Root;
int h[N],sum[N],vis[N],Cnt[M];
struct Node{int Min,Max;}P[N];
struct edge{int to,next,dist;}d[N*2];
void Add(int x,int y,int z){d[++cnt]=(edge){y,h[x],z};h[x]=cnt;}
bool cmp1(Node A,Node B){return A.Min!=B.Min?A.Min<B.Min:A.Max<B.Max;}
bool cmp2(Node A,Node B){return A.Min!=B.Min?A.Min<B.Min:A.Max>B.Max;}
void Find(int x,int fa,int num){
	int Max=0;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa||vis[y])continue;
		Find(y,x,num);
		sum[x]+=sum[y];
		Max=max(Max,sum[y]);
	}
	Max=max(Max,num-sum[x]);
	if(Max<Min){Min=Max;Root=x;}
}
void dfs(int x,int fa,int Min,int Max){
	sum[x]=1;
	if(fa)P[++tot]=(Node){Min,Max};
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa||vis[y])continue;
		dfs(y,x,min(Min,d[i].dist),max(Max,d[i].dist));
		sum[x]+=sum[y];
	}
}
struct Tree{
	int c[M];
	int lowbit(int x){return x&(-x);}
	void Add(int x,int y){for(;x<M;x+=lowbit(x))c[x]+=y;}
	int Ask(int x){int ans=0;for(;x>=1;x-=lowbit(x))ans+=c[x];return ans;}
}tree;
void Calc(int x,int fa,int f,int Min,int Max){
	tot=0;
	dfs(x,fa,Min,Max);
	sort(P+1,P+tot+1,cmp1);
	for(int i=1;i<=tot;i++)if(P[i].Max-P[i].Min<K)Cnt[P[i].Max]++;
	for(int i=1;i<=tot;i++)if(P[i].Max-P[i].Min<K){Cnt[P[i].Max]--;Ans+=f*Cnt[P[i].Min+K];}
	if(f==1)for(int i=1;i<=tot;i++)if(P[i].Max-P[i].Min==K)Ans++;
	sort(P+1,P+tot+1,cmp2);
	for(int i=tot;i>=1;i--){
		if(P[i].Max-P[i].Min==K)Ans+=tree.Ask(P[i].Max)*f;
		tree.Add(P[i].Max,1);
	}
	for(int i=1;i<=tot;i++)tree.Add(P[i].Max,-1);
}
void Divide(int x,int fa,int num){
	Root=0;Min=inf;Find(x,0,num);
	x=Root;vis[x]=1;Calc(x,0,1,inf,-inf);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(vis[y])continue;
		Calc(y,x,-1,d[i].dist,d[i].dist);
		Divide(y,x,sum[y]);
	}
}
int main(){
//	freopen("route.in","r",stdin);
//	freopen("route.out","w",stdout);
	n=read();K=read();
	for(int i=1;i<n;i++){int x=read(),y=read(),z=read();Add(x,y,z);Add(y,x,z);}
	Divide(1,0,n);
	printf("%lld\n",Ans);
	return 0;
}