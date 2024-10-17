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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,T,cnt,tot,len;
int h[N],b[N],prt[N],p[N][25];
int val[N],sum[N],vis[N],dep[N],root[N];
struct edge{int to,next;}d[N*20];
struct Tree{int l,r,sum;}t[N*200];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
int Find(int x){
	return x==prt[x]?x:prt[x]=Find(prt[x]);
}
int lca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int k=20;k>=0;k--){
		if(dep[x]-(1<<k)>=dep[y])x=p[x][k];
	}
	if(x==y)return x;
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--){
		if(p[x][k]!=p[y][k]){x=p[x][k];y=p[y][k];}
	}
	return p[x][0];
}
int Insert(int x,int pos,int l,int r){
	int y=++tot;
	t[y]=t[x];
	t[y].sum++;
	if(l==r)return y;
	int mid=(l+r)>>1;
	if(pos<=mid)t[y].l=Insert(t[x].l,pos,l,mid);
	if(pos>mid)t[y].r=Insert(t[x].r,pos,mid+1,r);
	return y;
}
int Ask(int x,int y,int fa,int gra,int k,int l,int r){
	if(l==r)return l;
	int mid=(l+r)>>1;
	int tmp=t[t[x].l].sum+t[t[y].l].sum;
	tmp-=t[t[fa].l].sum+t[t[gra].l].sum;
	if(k<=tmp)return Ask(t[x].l,t[y].l,t[fa].l,t[gra].l,k,l,mid);
	else return Ask(t[x].r,t[y].r,t[fa].r,t[gra].r,k-tmp,mid+1,r);
}
void DFS(int x,int father,int rt){
	vis[x]=1;sum[rt]++;
	dep[x]=dep[father]+1;
	prt[x]=p[x][0]=father;
	for(int i=1;i<=20;i++){
		p[x][i]=p[p[x][i-1]][i-1];
	}
	root[x]=Insert(root[prt[x]],val[x],1,len);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==father)continue;
		DFS(y,x,rt);
	}
}
void Build(){
	sort(b+1,b+len+1);
	len=unique(b+1,b+len+1)-b-1;
	for(int i=1;i<=n;i++){
		val[i]=lower_bound(b+1,b+len+1,val[i])-b;
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			DFS(i,0,i);
			prt[i]=i;
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int Case=read();
	n=read();m=read();T=read();
	for(int i=1;i<=n;i++){
		val[i]=b[++len]=read();
		prt[i]=i;
	}
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	Build();
	int lst=0;
	while(T--){
		char s[2];
		scanf("%s",s);
		int x=read()^lst,y=read()^lst;
		if(s[0]=='Q'){
			int k=read()^lst;
			int z=lca(x,y);int gra=p[z][0];
			lst=Ask(root[x],root[y],root[z],root[gra],k,1,len);
			printf("%d\n",lst=b[lst]);
		}
		if(s[0]=='L'){
			int fx=Find(x),fy=Find(y);
			if(sum[fx]<sum[fy]){
				swap(fx,fy);
				swap(x,y);
			}
			Add(x,y);Add(y,x);
			DFS(y,x,fx);
		}
	}
	return 0;
}