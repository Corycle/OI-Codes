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
const int N=200005;
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
int n,m,cnt=1;
int a[N],f[N],F[N],g[N],h[N],fa[N],w1[N],w2[N],sum[N];
int dep[N],son[N],top[N],Sumv[N],Sumf[N],dis1[N],dis2[N];
struct edge{int to,next,cost;}d[N*2];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
void DFS1(int x,int depth){
	dep[x]=depth;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;
		w1[y]=d[i].cost;
		w2[y]=d[i^1].cost;
		DFS1(y,depth+1);
		F[x]+=f[y];sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
		
	}
	f[x]=max(a[x]+F[x]-w1[x]-w2[x],0);
}
void DFS2(int x,int tp){
	top[x]=tp;
	Sumv[x]=Sumv[fa[x]]+a[x];
	Sumf[x]=Sumf[fa[x]]+F[fa[x]]-f[x];
	dis1[x]=dis1[fa[x]]+w1[x];
	dis2[x]=dis2[fa[x]]+w2[x];
	g[x]=max(a[fa[x]]+g[fa[x]]+F[fa[x]]-f[x]-w1[x]-w2[x],0);
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
	return dep[x]<dep[y]?x:y;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		int z1=read(),z2=read();
		Add(x,y,z1);Add(y,x,z2);
	}
	DFS1(1,1);DFS2(1,1);
	while(m--){
		int x=read(),y=read();
		int z=LCA(x,y);ll Ans=0;
		Ans+=F[x]+F[y]-F[z]+g[z];
		Ans+=Sumf[x]+Sumf[y]-Sumf[z]*2;
		Ans+=Sumv[x]+Sumv[y]-Sumv[z]*2+a[z];
		Ans-=dis2[x]-dis2[z]+dis1[y]-dis1[z];
		printf("%lld\n",Ans);
	}
	return 0;
}