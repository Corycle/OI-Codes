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
const int N=70005;
const int M=305;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans,a[N];
int n,m,type,cnt,tot;
int h[N],L[N],R[N],fa[N];
int dep[N],son[N],sum[N],top[N];
struct Edge{int x,y,dist;}e[N];
struct edge{int to,next,dist;}d[N*2];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
/*========Prepare========*/
void DFS1(int x,int depth){
	L[x]=++tot;
	dep[x]=depth;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;a[y]=d[i].dist;
		DFS1(y,depth+1);sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
	}
	R[x]=tot;
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
	return dep[x]<dep[y]?x:y;
}
/*========Operation========*/
int blk,num,st[N],ed[N],pos[N];
struct BIT{
	ll c[N];
	int lowbit(int x){return x&(-x);}
	void Add(int x,ll y){for(;x<=n;x+=lowbit(x))c[x]+=y;}
	ll Ask(int x){ll ans=0;for(;x>=1;x-=lowbit(x))ans+=c[x];return ans;}
}tree;
struct Block{
	ll ans;BIT bit;
	int bl,br,sum[N];
	void DFS(int x){
		sum[x]=(bl<=x&&x<=br);
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(y==fa[x])continue;
			DFS(y);sum[x]+=sum[y];
		}
		ans+=a[x]*sum[x];
		bit.Add(L[x],a[x]*sum[x]);
		bit.Add(R[x]+1,-a[x]*sum[x]);
	}
	void Change(int x,ll y){
		ans+=(y-a[x])*sum[x];
		bit.Add(L[x],(y-a[x])*sum[x]);
		bit.Add(R[x]+1,-(y-a[x])*sum[x]);
	}
	ll Ask(int x){
		return ans+(br-bl+1)*tree.Ask(L[x])-2*bit.Ask(L[x]);
	}
}block[M];
ll Dist(int x,int y){
	return tree.Ask(L[x])+tree.Ask(L[y])-tree.Ask(L[LCA(x,y)])*2;
}
void Modify(int id,int y){
	int x=(L[e[id].x]>L[e[id].y]?e[id].x:e[id].y);
	for(int i=1;i<=num;i++)block[i].Change(x,y);
	tree.Add(L[x],y-a[x]);
	tree.Add(R[x]+1,a[x]-y);
	a[x]=y;
}
void Query(int x,int ql,int qr){
	int l=pos[ql],r=pos[qr];Ans=0;
	if(l==r)for(int i=ql;i<=qr;i++)Ans+=Dist(x,i);
	else{
		for(int i=ql;i<=ed[l];i++)Ans+=Dist(x,i);
		for(int i=st[r];i<=qr;i++)Ans+=Dist(x,i);
		Ans+=block[r-1].Ask(x)-block[l].Ask(x);
	}
}
char s[M];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();type=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
		e[i]=(Edge){x,y,z};
	}
	DFS1(1,1);DFS2(1,1);
	blk=300;num=n/blk;
	for(int i=1;i<=num;i++){
		st[i]=ed[i-1]+1;
		ed[i]=ed[i-1]+blk;
	}
	if(ed[num]!=n){num++;st[num]=ed[num-1]+1;ed[num]=n;}
	for(int i=1;i<=num;i++){
		for(int j=st[i];j<=ed[i];j++)pos[j]=i;
		block[i].bl=1;
		block[i].br=ed[i];
		block[i].DFS(1);
	}
	for(int i=1;i<=n;i++){
		tree.Add(L[i],a[i]);
		tree.Add(R[i]+1,-a[i]);
	}
	while(m--){
		scanf("%s",s);
		if(s[0]=='m'){
			int x=read()^(type*Ans);
			int y=read()^(type*Ans);
			Modify(x,y);
		}
		if(s[0]=='q'){
			int l=read()^(type*Ans);
			int r=read()^(type*Ans);
			int x=read()^(type*Ans);
			Query(x,l,r);
			printf("%lld\n",Ans);
			Ans%=n;
		}
	}
	return 0;
}