/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<bitset>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#define ll long long
#define Bitset bitset<M>
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e5+5;
const int M=1e3+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot;
vector<int>G[N];
Bitset U,Prime,Answer;
int a[N],L[N],R[N],pos[N],vis[M];
int mod(int x){return x>=m?x-m:x;}
void DFS(int x,int fa){pos[L[x]=++tot]=x;for(auto y:G[x])if(y!=fa)DFS(y,x);R[x]=tot;}
struct Tree{Bitset a;int tag;};
struct Segment_Tree{
	Tree t[N*4];
	void update(int p,int v){t[p].tag=mod(t[p].tag+v);t[p].a=((t[p].a<<v)&U)|(t[p].a>>(m-v));}
	void Pushdown(int p){if(t[p].tag){update(p<<1,t[p].tag);update(p<<1|1,t[p].tag);t[p].tag=0;}}
	void Build(int p,int l,int r){
		if(l==r){t[p].a[a[pos[l]]]=1;return;}int mid=(l+r)>>1;
		Build(lson);Build(rson);t[p].a=t[p<<1].a|t[p<<1|1].a;
	}
	void Update(int x,int y,int v,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,v);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,v,lson);Update(x,y,v,rson);t[p].a=t[p<<1].a|t[p<<1|1].a;
	}
	void Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){Answer|=t[p].a;return;}
		int mid=(l+r)>>1;Pushdown(p);
		Query(x,y,lson);Query(x,y,rson);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=0;i<m;i++)U[i]=1;
	for(int i=1;i<=n;i++)a[i]=read()%m;
	for(int i=1;i<n;i++){int x=read(),y=read();G[x].push_back(y);G[y].push_back(x);}
	DFS(1,0);
	for(int i=2;i<m;i++)vis[i]=1;
	for(int i=2;i<m;i++)if(vis[i]){Prime[i]=1;for(int j=i*2;j<m;j+=i)vis[j]=0;}
	tree.Build(1,1,n);
	int Q=read();
	while(Q--){
		int op=read(),x=read();
		if(op==1)tree.Update(L[x],R[x],read()%m,1,1,n);
		if(op==2){Answer.reset();tree.Query(L[x],R[x],1,1,n);Answer&=Prime;printf("%d\n",Answer.count());}
	}
	return 0;
}
