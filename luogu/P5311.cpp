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
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,Min,Root;
struct edge{int to,next;}d[N*2];
int c[N],h[N],fa[N],sum[N],vis[N],Ans[N],pos[N];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
struct Node{
	int l,r,id,op;
	friend bool operator<(Node A,Node B){return A.l!=B.l?A.l>B.l:A.op<B.op;}
};
vector<Node>F[N],Q[N];
struct BIT{
	int c[N];
	int lowbit(int x){return x&(-x);}
	void Add(int x,int y){for(;x<=n;x+=lowbit(x))c[x]+=y;}
	int Ask(int x){int ans=0;for(;x>=1;x-=lowbit(x))ans+=c[x];return ans;}
	int Query(int l,int r){return Ask(r)-Ask(l-1);}
}tree;
void Find(int x,int Fa,int num){
	int S=0;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==Fa||vis[y])continue;
		Find(y,x,num);
		sum[x]+=sum[y];
		S=max(S,sum[y]);
	}
	S=max(S,num-sum[x]);
	if(S<Min){Min=S;Root=x;}
}
void Calc(int x,int Fa,int p,int Min,int Max){
	sum[x]=1;
	F[x].push_back((Node){Min,Max,p,0});
	Q[p].push_back((Node){Min,Max,c[x],0});
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==Fa||vis[y])continue;
		Calc(y,x,p,min(Min,y),max(Max,y));
		sum[x]+=sum[y];
	}
}
void Divide(int x,int Fa,int num){
	Root=0;Min=inf;Find(x,0,num);
	x=Root;vis[x]=1;fa[x]=Fa;Calc(x,0,x,x,x);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(vis[y])continue;
		Divide(y,x,sum[y]);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)c[i]=read();
	for(int i=1;i<n;i++){int x=read(),y=read();Add(x,y);Add(y,x);}
	Divide(1,0,n);
	for(int i=1;i<=m;i++){
		int l=read(),r=read(),x=read();
		for(auto tmp:F[x]){
			if(l<=tmp.l&&tmp.r<=r){
				Q[tmp.id].push_back((Node){l,r,i,1});
				break;
			}
		}
	}
	for(int i=1;i<=n;i++){
		sort(Q[i].begin(),Q[i].end());
		for(auto tmp:Q[i]){
			if(tmp.op==0){
				if(pos[tmp.id]>tmp.r){tree.Add(pos[tmp.id],-1);pos[tmp.id]=0;}
				if(pos[tmp.id]==0){pos[tmp.id]=tmp.r;tree.Add(pos[tmp.id],1);}
			}
			if(tmp.op==1)Ans[tmp.id]=tree.Query(tmp.l,tmp.r);
		}
		for(auto tmp:Q[i])if(tmp.op==0&&pos[tmp.id]){tree.Add(pos[tmp.id],-1);pos[tmp.id]=0;}
	}
	for(int i=1;i<=m;i++)printf("%d\n",Ans[i]);
	return 0;
}
