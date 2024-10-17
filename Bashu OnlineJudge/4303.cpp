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
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=400005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,tot,Sum;
int h[N],fa[N],id[N],tp[N],prt[N];
int dep[N],sum[N],son[N],pos[N],Min[N];
struct edge{int to,next,data;}d[N];
struct Edge{int s,t,data,num,usd;}e[N];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],z};h[y]=cnt;
}
bool cmp(Edge x,Edge y){
	return x.data<y.data;
}
int Find(int x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
void Kruskal(){
	int num=0;
	sort(e+1,e+m+1,cmp);
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++)pos[e[i].num]=i;
	for(int i=1;i<=m;i++){
		int x=Find(e[i].s);
		int y=Find(e[i].t);
		if(x==y)continue;
		e[i].usd=1;
		num++;fa[x]=y;
		Sum+=e[i].data;
		Add(e[i].s,e[i].t,e[i].data);
		if(num==n-1)break;
	}
	if(num!=n-1){
		int Q=read();
		while(Q--)printf("Not connected\n");
		exit(0);
	}
}
void DFS1(int x,int depth){
	sum[x]=1;
	dep[x]=depth;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==prt[x])continue;
		prt[y]=x;
		DFS1(y,depth+1);
		sum[x]+=sum[y];
		if(!son[x]||sum[y]>sum[son[x]])son[x]=y;
	}
}
void DFS2(int x,int top){
	tp[x]=top;
	id[x]=++tot;
	if(son[x])DFS2(son[x],top);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==prt[x]||y==son[x])continue;
		DFS2(y,y);
	}
}
void Pushdown(int num){
	Min[num<<1]=min(Min[num<<1],Min[num]);
	Min[num<<1|1]=min(Min[num<<1|1],Min[num]);
}
int Ask(int x,int num,int l,int r){
	if(x<l||x>r)return inf;
	if(l==r)return Min[num];
	Pushdown(num);
	int mid=(l+r)>>1;
	return min(Ask(x,lson),Ask(x,rson));
}
void Change(int x,int y,int z,int num,int l,int r){
	if(y<l||x>r)return;
	if(x<=l&&r<=y){
		Min[num]=min(Min[num],z);
		return;
	}
	Pushdown(num);
	int mid=(l+r)>>1;
	Change(x,y,z,lson);
	Change(x,y,z,rson);
}
void Update(int x,int y,int z){
	while(tp[x]!=tp[y]){
		if(dep[tp[x]]<dep[tp[y]])swap(x,y);
		Change(id[tp[x]],id[x],z,1,1,n);
		x=prt[tp[x]];
	}
	if(x==y)return;
	if(dep[x]>dep[y])swap(x,y);
	Change(id[son[x]],id[y],z,1,1,n);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		e[i].num=i;
		e[i].s=read();
		e[i].t=read();
		e[i].data=read();
	}
	Kruskal();
	DFS1(1,1);
	DFS2(1,1);
	memset(Min,0x3f,sizeof(Min));
	for(int i=1;i<=m;i++){
		if(dep[e[i].s]<dep[e[i].t])swap(e[i].s,e[i].t);
		if(!e[i].usd)Update(e[i].s,e[i].t,e[i].data);
	}
	int T=read();
	while(T--){
		int i=pos[read()];
		if(!e[i].usd){
			printf("%d\n",Sum);
			continue;
		}
		int dlt=Ask(id[e[i].s],1,1,n);
		if(dlt==inf)printf("Not connected\n");
		else printf("%d\n",Sum+dlt-e[i].data);
	}
	return 0;
}