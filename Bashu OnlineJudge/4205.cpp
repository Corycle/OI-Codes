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
#include<set>
#define ll long long
#define set_it set<int>::iterator
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
int n,m,cnt,tot;
int b[N],c[N],fa[N],dep[N],sum[N];
int h[N],id[N],pos[N],p[N][M],Root[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
struct Tree{int l,r,sum;};
struct Segment_Tree{
	int tot;
	Tree t[N*M*4];
	int NewNode(){t[++tot]=(Tree){0,0,0};return tot;}
	void Insert(int &x,int y,int pos,int val,int l,int r){
		x=NewNode();t[x]=t[y];t[x].sum+=val;
		if(l==r)return;int mid=(l+r)>>1;
		if(pos<=mid)Insert(t[x].l,t[y].l,pos,val,l,mid);
		if(pos>mid)Insert(t[x].r,t[y].r,pos,val,mid+1,r);
	}
	int Query(int p,int x,int y,int l,int r){
		if(y<l||x>r||!p)return 0;
		if(x<=l&&r<=y)return t[p].sum;
		int mid=(l+r)>>1;
		return Query(t[p].l,x,y,l,mid)+Query(t[p].r,x,y,mid+1,r);
	}
}tree;
set<int>F[N];
void Prepare(){
	tree.tot=cnt=tot=0;
	for(int i=1;i<=n;i++){
		h[i]=dep[i]=fa[i]=Root[i]=0;
		for(int j=0;j<M;j++)p[i][j]=0;
	}
}
bool cmp(int x,int y){return dep[x]<dep[y];}
void DFS(int x,int depth){
	sum[x]=1;dep[x]=depth;
	pos[id[x]=++tot]=x;p[x][0]=fa[x];
	for(int i=1;i<M;i++)p[x][i]=p[p[x][i-1]][i-1];
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		DFS(y,depth+1);
		sum[x]+=sum[y];
	}
}
int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--){
		if(dep[x]-(1<<k)>=dep[y])x=p[x][k];
	}
	if(x==y)return x;
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--){
		if(p[x][k]!=p[y][k]){x=p[x][k];y=p[y][k];}
	}
	return p[x][0];
}
void Insert(int x,int c,int i){
	F[c].insert(id[x]);
	tree.Insert(Root[i],Root[i],id[x],1,1,n);
	set_it P=F[c].find(id[x]),L=P,R=P;
	if(P!=F[c].begin())L--;
	if(P!=--F[c].end())R++;
	int l=pos[*L],r=pos[*R];
//	for(auto y:F[c])cout<<pos[y]<<" ";cout<<endl;
//	cout<<"dep: "<<i<<" "<<"pos: "<<id[x]<<":"<<x<<" "<<l<<" "<<r<<endl;
	if(x!=l)tree.Insert(Root[i],Root[i],id[LCA(x,l)],-1,1,n);
	if(x!=r)tree.Insert(Root[i],Root[i],id[LCA(x,r)],-1,1,n);
	if(x!=l&&x!=r)tree.Insert(Root[i],Root[i],id[LCA(l,r)],1,1,n);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int Case=read();
	while(Case--){
		n=read();m=read();Prepare();
		for(int i=1;i<=n;i++)c[i]=read();
		for(int i=2;i<=n;i++)Add(fa[i]=read(),i);
		DFS(1,1);
		for(int i=1;i<=n;i++)b[i]=i;
		sort(b+1,b+n+1,cmp);
		for(int i=1;i<=n;i++){
			int x=b[i],y=b[i-1];
			Root[dep[x]]=Root[dep[y]];
			Insert(x,c[x],dep[x]);
		}
		int Ans=0,Max=dep[b[n]];
		while(m--){
			int x=read()^Ans,d=read()^Ans;
			int rt=Root[min(dep[x]+d,Max)];
//			cout<<"Query: "<<x<<" "<<d<<" = ";
			printf("%d\n",Ans=tree.Query(rt,id[x],id[x]+sum[x]-1,1,n));
		}
		for(int i=1;i<=n;i++)F[i].clear();
	}
	return 0;
}