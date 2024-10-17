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
#define lson t[p].l,l,mid
#define rson t[p].r,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,dfn;
int h[N],w[N],c[N],fa[N],rt[N],dep[N];
int sum[N],son[N],top[N],pos[N],id[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS1(int x,int depth){
	dep[x]=depth;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;fa[y]=x;
		DFS1(y,depth+1);sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
	}
}
void DFS2(int x,int tp){
	top[x]=tp;pos[id[x]=++dfn]=x;
	if(son[x])DFS2(son[x],tp);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x]||y==son[x])continue;
		DFS2(y,y);
	}
}
struct Segment_Tree{
	int tot;
	struct Tree{int l,r,sum,Max;}t[N*50];
	void Pushup(int p){
		t[p].sum=t[t[p].l].sum+t[t[p].r].sum;
		t[p].Max=max(t[t[p].l].Max,t[t[p].r].Max);
	}
	void Init(int p,int l,int C){
		t[p].sum=(c[pos[l]]==C?w[pos[l]]:0);
		t[p].Max=(c[pos[l]]==C?w[pos[l]]:-inf);
	}
	void Change(int x,int y,int &p,int l,int r){
		if(!p)p=++tot;
		if(l==r){Init(p,l,y);return;}
		int mid=(l+r)>>1;
		if(x<=mid)Change(x,y,lson);
		if(x>mid) Change(x,y,rson);
		Pushup(p);
	}
	int Sum(int x,int y,int p,int l,int r){
		if(y<l||x>r||!p)return 0;
		if(x<=l&&r<=y)return t[p].sum;
		int mid=(l+r)>>1;
		return Sum(x,y,lson)+Sum(x,y,rson);
	}
	int Max(int x,int y,int p,int l,int r){
		if(y<l||x>r||!p)return -inf;
		if(x<=l&&r<=y)return t[p].Max;
		int mid=(l+r)>>1;
		return max(Max(x,y,lson),Max(x,y,rson));
	}
}tree;
void Change1(int x,int y){
	int z=c[x];c[x]=y;
	tree.Change(id[x],y,rt[y],1,n);
	tree.Change(id[x],z,rt[z],1,n);
}
void Change2(int x,int y){
	w[x]=y;
	tree.Change(id[x],c[x],rt[c[x]],1,n);
}
int Sum(int x,int y){
	int C=c[x],ans=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		ans+=tree.Sum(id[top[x]],id[x],rt[C],1,n);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	ans+=tree.Sum(id[x],id[y],rt[C],1,n);
	return ans;
}
int Max(int x,int y){
	int C=c[x],ans=-inf;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		ans=max(ans,tree.Max(id[top[x]],id[x],rt[C],1,n));
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	ans=max(ans,tree.Max(id[x],id[y],rt[C],1,n));
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		w[i]=read();
		c[i]=read();
	}
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS1(1,1);DFS2(1,1);
	for(int i=1;i<=n;i++){
		tree.Change(id[i],c[i],rt[c[i]],1,n);
	}
	char op[5];
	while(m--){
		scanf("%s",op);
		int x=read(),y=read();
		if(op[1]=='C')Change1(x,y);
		if(op[1]=='W')Change2(x,y);
		if(op[1]=='S')printf("%d\n",Sum(x,y));
		if(op[1]=='M')printf("%d\n",Max(x,y));
	}
	return 0;
}