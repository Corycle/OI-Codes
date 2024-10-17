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
using namespace std;
const int inf=0x3f3f3f3f;
const int M=500005;
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Q,lst;
int cnt,Cnt,tot,step,total;
int L[N],R[N],h[N],b[N],fa[N];
int dep[N],sum[N],prt[N],val[N];
int pos[N],root[N],Height[N],p[N][35];
struct edge{int to,next;}d[M];
struct Edge{int s,t,data;}e[M];
struct Tree{int l,r,sum;}t[M*20];
bool cmp(Edge x,Edge y){return x.data<y.data;}
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void Kruskal(){
	int num=n;
	sort(e+1,e+m+1,cmp);
	for(int i=1;i<=tot;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		int x=Find(e[i].s);
		int y=Find(e[i].t);
		if(x==y)continue;
		fa[x]=fa[y]=++num;
		val[num]=e[i].data;
		Add(num,x);Add(num,y);
		if(num==tot)break;
	}
	tot=num;
}
void DFS(int x,int depth){
	dep[x]=depth;
	L[x]=inf;R[x]=0;
	if(x<=n){
		pos[++step]=x;
		L[x]=R[x]=step;
		return;
	}
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(dep[y])continue;
		DFS(y,depth+1);
		prt[y]=x;
		L[x]=min(L[x],L[y]);
		R[x]=max(R[x],R[y]);
	}
}
int Insert(int data,int x,int l,int r){
	int y=++total;
	t[y].sum=t[x].sum+1;
	if(l==r)return y;
	int mid=(l+r)>>1;
	t[y].l=t[x].l;t[y].r=t[x].r;
	if(data<=mid)t[y].l=Insert(data,t[x].l,l,mid);
	else t[y].r=Insert(data,t[x].r,mid+1,r);
	return y;
}
int Query(int k,int x,int y,int l,int r){
	if(l==r)return l;
	int mid=(l+r)>>1;
	int z=t[t[y].r].sum-t[t[x].r].sum;
	if(k<=z)return Query(k,t[x].r,t[y].r,mid+1,r);
	else return Query(k-z,t[x].l,t[y].l,l,mid);
}
void ST(){
	memset(p,-1,sizeof(p));
	int k=(int)(log(n)/log(2));
	for(int i=1;i<=tot;i++)if(prt[i])p[i][0]=prt[i];
	for(int j=1;j<=k;j++){
		for(int i=1;i<=tot;i++){
			if(p[i][j-1]!=-1)p[i][j]=p[p[i][j-1]][j-1];
		}
	}
}
int Ask(int x,int y){
	int k=(int)(log(dep[x])/log(2));
	for(;k>=0;k--){
		if(p[x][k]!=-1&&val[p[x][k]]&&val[p[x][k]]<=y)x=p[x][k];
	}
	return x;
}
void Init(){
	tot=n+n-1;
	sort(b+1,b+Cnt+1);
	Cnt=unique(b+1,b+Cnt+1)-b-1;
	for(int i=1;i<=n;i++){
		Height[i]=lower_bound(b+1,b+Cnt+1,Height[i])-b;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Q=read();
	for(int i=1;i<=n;i++){
		Height[i]=read();
		b[++Cnt]=Height[i];
	}
	for(int i=1;i<=m;i++){
		e[i].s=read();
		e[i].t=read();
		e[i].data=read();
	}
	Init();
	Kruskal();
	DFS(tot,1);
	ST();
	for(int i=1;i<=n;i++){
		root[i]=Insert(Height[pos[i]],root[i-1],1,Cnt);
	}
	while(Q--){
		int x=read()^lst,y=read()^lst,k=read()^lst;
		int fx=Ask(x,y);
		int l=L[fx],r=R[fx];
		if(k>t[root[r]].sum-t[root[l-1]].sum){
			lst=0;
			printf("-1\n");
			continue;
		}
		int ans=Query(k,root[l-1],root[r],1,Cnt);
		printf("%d\n",b[ans]);
		lst=b[ans];
	}
	return 0;
}