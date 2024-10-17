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
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e5+5;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,tot;
int h[N],fa[N],id[N],pos[N],sum[N],dep[N],p[N][M];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
struct Node{int val,tag;};
struct Segment_Tree{
	Node t[N*4];
	void update(int p,int x){t[p].val+=x;t[p].tag+=x;}
	void Pushdown(int p){
		if(t[p].tag){
			update(p<<1,t[p].tag);
			update(p<<1|1,t[p].tag);
			t[p].tag=0;
		}
	}
	void Build(int p,int l,int r){
		if(l==r){t[p].val=dep[pos[l]];return;}
		int mid=(l+r)>>1;
		Build(lson);Build(rson);
		t[p].val=max(t[p<<1].val,t[p<<1|1].val);
	}
	void Update(int x,int y,int v,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,v);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,v,lson);Update(x,y,v,rson);
		t[p].val=max(t[p<<1].val,t[p<<1|1].val);
	}
	int Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].val;
		int mid=(l+r)>>1;Pushdown(p);
		return max(Query(x,y,lson),Query(x,y,rson));
	}
}tree;
struct Tree{int ch[2],fa,aux;};
struct Link_Cut_Tree{
	Tree t[N];
	void Rotate(int x){
		int y=t[x].fa;int z=t[y].fa;
		int l=(x!=t[y].ch[0]),r=l^1;
		if(t[y].aux)t[z].ch[y!=t[z].ch[0]]=x;
		else{t[x].aux=0;t[y].aux=1;}
		t[x].fa=z;t[y].fa=x;
		t[t[x].ch[r]].fa=y;
		t[y].ch[l]=t[x].ch[r];
		t[x].ch[r]=y;
	}
	void Splay(int x){
		while(t[x].aux){
			int y=t[x].fa,z=t[y].fa;
			if(t[y].aux){
				if((x==t[y].ch[0])^(y==t[z].ch[0]))Rotate(x);
				else Rotate(y);
			}
			Rotate(x);
		}
	}
	int Find(int x){while(t[x].ch[0])x=t[x].ch[0];return x;}
	void Update(int x,int v){tree.Update(id[x],id[x]+sum[x]-1,v,1,1,n);}
	void Access(int x){
		int y=0;
		while(x){
			Splay(x);
			if(t[x].ch[1])Update(Find(t[x].ch[1]),1);
			t[t[x].ch[1]].aux=0;
			t[x].ch[1]=y;
			t[t[x].ch[1]].aux=1;
			if(t[x].ch[1])Update(Find(t[x].ch[1]),-1);
			y=x;x=t[x].fa;
		}
	}
}lct;
void DFS(int x,int depth){
	sum[x]=1;dep[x]=depth;
	pos[id[x]=++tot]=x;p[x][0]=fa[x];
	for(int i=1;i<M;i++)p[x][i]=p[p[x][i-1]][i-1];
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;
		lct.t[y].fa=x;
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
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS(1,1);
	tree.Build(1,1,n);
	while(m--){
		int op=read();
		if(op==1)lct.Access(read());
		if(op==2){
			int x=read(),y=read(),z=LCA(x,y);
			int Ans1=tree.Query(id[x],id[x],1,1,n);
			int Ans2=tree.Query(id[y],id[y],1,1,n);
			int Ans3=tree.Query(id[z],id[z],1,1,n);
			printf("%d\n",Ans1+Ans2-Ans3*2+1);
		}
		if(op==3){
			int x=read();
			printf("%d\n",tree.Query(id[x],id[x]+sum[x]-1,1,1,n));
		}
	}
	return 0;
}