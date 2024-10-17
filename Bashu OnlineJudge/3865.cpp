#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot,cnt;
int a[N],b[N],h[N],dep[N];
int p[N][25],root[N],cntt,prt[N];
struct edge{
	int to,next;
}d[N*2];
struct tree{
	int s,l,r;
}t[N*40];
void edge_add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
int Insert(int l,int r,int x,int pos){
	int y=++cntt;
	t[y].s=t[x].s+1;
	if(l==r)return y;
	t[y].l=t[x].l;
	t[y].r=t[x].r;
	int mid=(l+r)>>1;
	if(pos<=mid)t[y].l=Insert(l,mid,t[x].l,pos);
	else t[y].r=Insert(mid+1,r,t[x].r,pos);
	return y;
}
void dfs(int x,int depth){
	dep[x]=depth;
	root[x]=Insert(1,tot,root[prt[x]],a[x]);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(dep[y])continue;
		p[y][0]=prt[y]=x;
		dfs(y,depth+1);
	}
}
void ST(){
	int k=(int)(log(n)/log(2));
	for(int j=1;j<=k;j++){
		for(int i=1;i<=n;i++){
			if(p[i][j-1]!=-1)p[i][j]=p[p[i][j-1]][j-1];
		}
	}
}
int lca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	int k=(int)(log(n)/log(2));
	for(k;k>=0;k--){
		if(dep[x]-(1<<k)>=dep[y])x=p[x][k];
	}
	if(x==y)return x;
	k=(int)(log(n)/log(2));
	for(k;k>=0;k--){
		if(p[x][k]!=p[y][k]){
			x=p[x][k];
			y=p[y][k];
		}
	}
	return p[x][0];
}
int Ask(int l,int r,int x,int y,int fa,int gra,int k){
	if(l==r)return l;
	int mid=(l+r)>>1;
	int tmp=t[t[x].l].s+t[t[y].l].s-t[t[fa].l].s-t[t[gra].l].s;
	if(tmp>=k)return Ask(l,mid,t[x].l,t[y].l,t[fa].l,t[gra].l,k);
	else return Ask(mid+1,r,t[x].r,t[y].r,t[fa].r,t[gra].r,k-tmp);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		a[i]=b[i]=read();
	}
	sort(b+1,b+n+1);
	tot=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(b+1,b+tot+1,a[i])-b;
	}
	for(int i=1;i<=n-1;i++){
		int x=read(),y=read();
		edge_add(x,y);
		edge_add(y,x);
	}
	memset(p,-1,sizeof(p));
	dfs(1,1);
	ST();
	int lst=0;
	while(m--){
		int x=read()^lst,y=read(),k=read();
		int z=lca(x,y);
		int ans=Ask(1,tot,root[x],root[y],root[z],root[prt[z]],k);
		printf("%d\n",lst=b[ans]);
	}
	return 0;
}