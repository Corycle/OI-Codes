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
const int N=100005;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>V[N];
int n,m,Q,cnt,Ans,Max,Ansx,Ansy;
int c[N],h[N],fa[N],p1[N],p2[N],len[N];
int p[N][M],dep[N],top[N],sum[N],son[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
void DFS1(int x,int depth){
	dep[x]=depth;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;fa[y]=x;
		DFS1(y,depth+1);sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
	}
}
void DFS2(int x,int tp){
	top[x]=tp;
	if(son[x])DFS2(son[x],tp);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x]||y==son[x])continue;
		DFS2(y,y);
	}
}
int LCA(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x=fa[top[x]];
	}
	if(dep[x]<dep[y])return x;
	return y;
}
int Dist(int x,int y){
	return dep[x]+dep[y]-dep[LCA(x,y)]*2+1;
}
void Update(int x){
	if(!len[x])return;
	if(!Ansx){Max=len[x];Ansx=p1[x];Ansy=p2[x];return;}
	int sx=Ansx,tx=Ansy,sy=p1[x],ty=p2[x],dlt=0;
	if(len[x]>Max){Max=len[x];Ansx=p1[x];Ansy=p2[x];}
	Ans=max(Ans,dlt=Dist(sx,sy));if(dlt>Max){Max=dlt;Ansx=sx;Ansy=sy;}
	Ans=max(Ans,dlt=Dist(sx,ty));if(dlt>Max){Max=dlt;Ansx=sx;Ansy=ty;}
	Ans=max(Ans,dlt=Dist(tx,sy));if(dlt>Max){Max=dlt;Ansx=tx;Ansy=sy;}
	Ans=max(Ans,dlt=Dist(tx,ty));if(dlt>Max){Max=dlt;Ansx=tx;Ansy=ty;}
}
int main(){
//	freopen("tour.in","r",stdin);
//	freopen("tour.out","w",stdout);
	n=read();m=read();Q=read();
	for(int i=1;i<=n;i++){
		c[i]=read();
		V[c[i]].push_back(i);
	}
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS1(1,1);DFS2(1,1);
	for(int i=1;i<=n;i++){
		int num=V[i].size();
		if(!num)continue;
		len[i]=1;p1[i]=p2[i]=V[i][0];
		for(int j=1;j<num;j++){
			int x=V[i][j],sx=p1[i],sy=p2[i],dlt=0;
			dlt=Dist(sx,x);if(dlt>len[i]){len[i]=dlt;p1[i]=sx;p2[i]=x;}
			dlt=Dist(sy,x);if(dlt>len[i]){len[i]=dlt;p1[i]=sy;p2[i]=x;}
		}
	}
	while(Q--){
		int k=read();
		Ans=-1;Max=Ansx=Ansy=0;
		for(int i=1;i<=k;i++)Update(read());
		printf("%d\n",Ans);
	}
	return 0;
}