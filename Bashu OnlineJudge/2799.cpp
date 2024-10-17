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
const int N=80005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot,cnt,step,cntt;
int t1[N],t2[N],t3[N],t4[N];
int p[N][25],root[N*5],b[N*5];
int a[N],h[N],l[N],r[N],dep[N],prt[N];
struct tree{
	int l,r,s;
}t[N*400];
struct edge{
	int to,next;
}d[N*2];
struct ques{
	int k,x,y;
}q[N];
void edge_add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
int Insert(int l,int r,int x,int data,int addv){
	int y=++cntt;
	t[y].s=t[x].s+addv;
	if(l==r)return y;
	t[y].l=t[x].l;
	t[y].r=t[x].r;
	int mid=(l+r)>>1;
	if(data<=mid)t[y].l=Insert(l,mid,t[x].l,data,addv);
	else t[y].r=Insert(mid+1,r,t[x].r,data,addv);
	return y;
}
int lowbit(int x){
	return x&(-x);
}
void Add(int p,int x,int y){
	for(int i=p;i<=n;i+=lowbit(i)){
		root[i]=Insert(1,tot,root[i],x,y);
	}
}
void dfs(int x,int depth){
	l[x]=++step;
	dep[x]=depth;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(dep[y])continue;
		p[y][0]=prt[y]=x;
		dfs(y,depth+1);
	}
	r[x]=step;
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
int Solve(int l,int r,int k){
	if(l==r)return l;
	int mid=(l+r)>>1;
	int tmp=0;
	for(int i=1;i<=t1[0];i++)tmp+=t[t[t1[i]].l].s;
	for(int i=1;i<=t2[0];i++)tmp+=t[t[t2[i]].l].s;
	for(int i=1;i<=t3[0];i++)tmp-=t[t[t3[i]].l].s;
	for(int i=1;i<=t4[0];i++)tmp-=t[t[t4[i]].l].s;
	if(tmp>=k){
		for(int i=1;i<=t1[0];i++)t1[i]=t[t1[i]].l;
		for(int i=1;i<=t2[0];i++)t2[i]=t[t2[i]].l;
		for(int i=1;i<=t3[0];i++)t3[i]=t[t3[i]].l;
		for(int i=1;i<=t4[0];i++)t4[i]=t[t4[i]].l;
		return Solve(l,mid,k);
	}
	else{
		for(int i=1;i<=t1[0];i++)t1[i]=t[t1[i]].r;
		for(int i=1;i<=t2[0];i++)t2[i]=t[t2[i]].r;
		for(int i=1;i<=t3[0];i++)t3[i]=t[t3[i]].r;
		for(int i=1;i<=t4[0];i++)t4[i]=t[t4[i]].r;
		return Solve(mid+1,r,k-tmp);
	}
}
int Ask(int x,int y,int fa,int gra,int k){
	t1[0]=t2[0]=t3[0]=t4[0]=0;
	int sum=dep[x]+dep[y]-dep[fa]-dep[gra];
	if(sum<k)return -1;
	k=sum-k+1;
	for(int i=l[x];i>=1;i-=lowbit(i))t1[++t1[0]]=root[i];
	for(int i=l[y];i>=1;i-=lowbit(i))t2[++t2[0]]=root[i];
	for(int i=l[fa];i>=1;i-=lowbit(i))t3[++t3[0]]=root[i];
	for(int i=l[gra];i>=1;i-=lowbit(i))t4[++t4[0]]=root[i];
	return Solve(1,tot,k);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		a[i]=b[i]=read();
	}
	for(int i=1;i<=n-1;i++){
		int x=read(),y=read();
		edge_add(x,y);edge_add(y,x);
	}
	tot=n;
	for(int i=1;i<=m;i++){
		q[i].k=read();
		q[i].x=read();q[i].y=read();
		if(q[i].k==0)b[++tot]=q[i].y;
	}
	sort(b+1,b+tot+1);
	tot=unique(b+1,b+tot+1)-b-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(b+1,b+tot+1,a[i])-b;
	}
	memset(p,-1,sizeof(p));
	dfs(1,1);
	ST();
	for(int i=1;i<=n;i++){
		Add(l[i],a[i],1);
		Add(r[i]+1,a[i],-1);
	}
	for(int i=1;i<=m;i++){
		int k=q[i].k,x=q[i].x,y=q[i].y;
		if(k==0){
			q[i].y=lower_bound(b+1,b+tot+1,q[i].y)-b;
			Add(l[x],a[x],-1);
			Add(r[x]+1,a[x],1);
			a[x]=q[i].y;
			Add(l[x],a[x],1);
			Add(r[x]+1,a[x],-1);
		}
		else{
			int z=lca(x,y);
			int ans=Ask(x,y,z,prt[z],k);
			if(ans==-1)printf("invalid request!\n");
			else printf("%d\n",b[ans]);
		}
	}
	return 0;
}