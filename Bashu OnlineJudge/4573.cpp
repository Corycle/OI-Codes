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
#define vec_it vector<Node>::iterator
using namespace std;
const ll inf=9e18;
const int N=150005;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Max,cnt,Min,Root;ll Ans;
int a[N],h[N],fa[N],sum[N],vis[N];
struct edge{int to,next,dist;}d[N*2];
struct Node{
	int x,sum;ll dist;
	friend bool operator<(Node A,Node B){return A.x<B.x;}
};
struct Tree{int x,t;ll dist;};
vector<Node>F[N][3];
vector<Tree>prt[N];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
void Find(int x,int Fa,int Size){
	int S=0;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==Fa||vis[y])continue;
		Find(y,x,Size);
		sum[x]+=sum[y];
		S=max(S,sum[y]);
	}
	S=max(S,Size-sum[x]);
	if(S<Min){Min=S;Root=x;}
}
void dfs(int x,int Fa,ll dist,int pre,int t){
	sum[x]=1;
	prt[x].push_back((Tree){pre,t,dist});
	F[pre][t].push_back((Node){a[x],1,dist});
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==Fa||vis[y])continue;
		dfs(y,x,dist+d[i].dist,pre,t);
		sum[x]+=sum[y];
	}
}
void Calc(int y,int x,int t,ll dist){
	dfs(y,x,dist,x,t);
	F[x][t].push_back((Node){-1,0,0});
	sort(F[x][t].begin(),F[x][t].end());
	for(int i=1;i<=sum[y];i++){
		F[x][t][i].dist+=F[x][t][i-1].dist;
	}
}
void Divide(int x,int Fa,int Size){
	Root=0;Min=Size;Find(x,0,Size);
	x=Root;vis[x]=1;fa[x]=Fa;
	prt[x].push_back((Tree){x,-1,0});
	for(int i=h[x],t=0;i;i=d[i].next){
		int y=d[i].to;
		if(vis[y])continue;
		Calc(y,x,t,d[i].dist);
		Divide(y,x,sum[y]);
		t++;
	}
}
ll Ask(vector<Node>&F,int L,int R,ll dist){
	vec_it l=--lower_bound(F.begin(),F.end(),(Node){L,0});
	vec_it r=--upper_bound(F.begin(),F.end(),(Node){R,0});
	return ((*r).dist-(*l).dist)+(r-l)*dist;
}
ll Query(int x,int L,int R){
	ll ans=0;
	for(int k=prt[x].size()-1;k>=0;k--){
		int t=prt[x][k].t;
		int fx=prt[x][k].x;
		ll dist=prt[x][k].dist;
		for(int i=0;i<=2;i++){
			if(i==t||F[fx][i].empty())continue;
			ans+=Ask(F[fx][i],L,R,dist);
		}
		if(L<=a[fx]&&a[fx]<=R)ans+=dist;
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Max=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	Divide(1,0,n);
	while(m--){
		int x=read();
		int L=(read()+Ans)%Max;
		int R=(read()+Ans)%Max;
		if(L>R)swap(L,R);
		printf("%lld\n",Ans=Query(x,L,R));
	}
	return 0;
}