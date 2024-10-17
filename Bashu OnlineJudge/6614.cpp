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
const int N=1e5+5;
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
vector<int>G[N];
struct Node{int k,id;};
vector<Node>F1[N],F2[N],Anc[N];
int n,m,cnt,Dis,Min,Root;
struct edge{int to,next;}d[N*2];
int h[N],c[N],prt[N],pre[N],sum[N],vis[N],Ans[N];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
/*========Part 1========*/
void Find(int x,int Fa,int Num){
	int Max=0;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;if(y==Fa||vis[y])continue;
		Find(y,x,Num);sum[x]+=sum[y];Max=max(Max,sum[y]);
	}
	Max=max(Max,Num-sum[x]);
	if(Max<Min){Min=Max;Root=x;}
}
void dfs(int x,int Fa,int dist){
	sum[x]=1;Anc[x].push_back((Node){dist,Root});
	for(int i=h[x];i;i=d[i].next){int y=d[i].to;if(y==Fa||vis[y])continue;dfs(y,x,dist+1);sum[x]+=sum[y];}
}
int Divide(int x,int Fa,int Num){
	Root=0;Min=inf;Find(x,0,Num);x=Root;vis[x]=1;dfs(x,0,0);prt[x]=Fa;G[Fa].push_back(x);
	for(int i=h[x];i;i=d[i].next){int y=d[i].to;if(!vis[y])pre[Divide(y,x,sum[y])]=y;}
	return x;
}
/*========Part 2========*/
void Calc(int x,int Fa,int dist){
	c[dist]++;
	for(int i=h[x];i;i=d[i].next){int y=d[i].to;if(y==Fa||vis[y])continue;Calc(y,x,dist+1);}
}
void Update(int x,int Sum,int dist){for(int i=0;i<=Sum;i++)c[i]=0;Calc(x,0,dist);}
void Solve(int x){
	vis[x]=1;Update(x,sum[x],0);
	for(auto tmp:F1[x])if(tmp.k<=sum[x])Ans[tmp.id]+=c[tmp.k];
	for(int i=G[x].size()-1;i>=0;i--){
		int y=G[x][i],fx=pre[y];
		Update(fx,sum[y],0);
		for(auto tmp:F2[y])if(tmp.k<=sum[y])Ans[tmp.id]-=c[tmp.k];
		Solve(y);
	}
}
int main(){
//	freopen("message.in","r",stdin);
//	freopen("message.out","w",stdout);
	int Case=read();
	while(Case--){
		n=read();m=read();cnt=0;
		for(int i=1;i<=n;i++)h[i]=prt[i]=vis[i]=0;
		for(int i=1;i<n;i++){int x=read(),y=read();Add(x,y);Add(y,x);}
		Divide(1,0,n);
		for(int i=1;i<=m;i++){
			int t=read(),k=read(),lst=0;Ans[i]=0;
			for(int j=Anc[t].size()-1;j>=0;j--){
				int x=Anc[t][j].id,dist=k-Anc[t][j].k;
				if(dist>=0){
					F1[x].push_back((Node){dist,i});
					if(dist>=1)F2[lst].push_back((Node){dist-1,i});
				}
				lst=x;
			}
		}
		for(int i=1;i<=n;i++){vis[i]=0;if(!prt[i])Root=i;}
		Solve(Root);
		for(int i=1;i<=m;i++)printf("%d\n",Ans[i]);
		for(int i=0;i<=n;i++){G[i].clear();F1[i].clear();F2[i].clear();Anc[i].clear();}
	}
	return 0;
}