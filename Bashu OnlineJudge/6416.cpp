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
const int M=22;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>P[N];
int n,m,cnt,dfn;
int h[N],L[N],R[N],fa[N],pos[N],dep[N],root[N],p[N][M];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS(int x,int depth){
	dep[x]=depth;
	L[x]=++dfn;pos[dfn]=x;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;DFS(y,depth+1);
	}
	R[x]=dfn;
}
void ST(){
	int k=(int)(log(n)/log(2));
	for(int i=1;i<=n;i++)p[i][0]=fa[i];
	for(int j=1;j<=k;j++){
		for(int i=1;i<=n;i++){
			if(p[i][j-1])p[i][j]=p[p[i][j-1]][j-1];
		}
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
struct Tree{int l,r,sum;};
struct Segment_Tree{
	int tot;Tree t[N*M*2];
	void Insert(int &x,int y,int data,int l,int r){
		x=++tot;t[x]=t[y];t[x].sum++;
		if(l==r)return;int mid=(l+r)>>1;
		if(data<=mid)Insert(t[x].l,t[y].l,data,l,mid);
		if(data>mid)Insert(t[x].r,t[y].r,data,mid+1,r);
	}
	int Ask(int x,int y,int k,int l,int r){
		if(k<0)return -1;
		if(l==r)return l;int mid=(l+r)>>1;
		int dlt=t[t[y].l].sum-t[t[x].l].sum;
		if(k<=dlt)return Ask(t[x].l,t[y].l,k,l,mid);
		else return Ask(t[x].r,t[y].r,k-dlt,mid+1,r);
	}
}tree;
int main(){
//	freopen("triumph.in","r",stdin);
//	freopen("triumph.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS(1,1);ST();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		int z=LCA(x,y);
		P[x].push_back(dep[z]);
		P[y].push_back(dep[z]);
	}
	root[0]=++tree.tot;
	for(int i=1;i<=n;i++){
		int x=pos[i];
		int num=P[x].size();
		if(!num)root[i]=root[i-1];
		else{
			tree.Insert(root[i],root[i-1],P[x][0],1,n);
			for(int j=1;j<num;j++){
				tree.Insert(root[i],root[i],P[x][j],1,n);
			}
		}
	}
	int T=read();
	while(T--){
		int x=read(),k=read();
		int depth=tree.Ask(root[L[x]-1],root[R[x]],k,1,n);
		if(depth<0||depth>dep[x])printf("0\n");
		else printf("%d\n",dep[x]-depth);
	}
	return 0;
}