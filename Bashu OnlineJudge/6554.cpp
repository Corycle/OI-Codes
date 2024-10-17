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
#include<unordered_map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int Mod=1e9+7;
const int Lim=1e9;
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N],F[N];
unordered_map<int,bool>vis[N];
int n,a[N],f[N],dis[N],Root[N];
int mod(int x){return x>=Mod?x-Mod:x;}
struct Tree{int l,r,sum,tag;};
struct Segment_Tree{
	int tot;
	Tree t[N*40];
	void update(int p,int x){
		t[p].sum=1ll*t[p].sum*x%Mod;
		t[p].tag=1ll*t[p].tag*x%Mod;
	}
	void Pushdown(int p){
		if(t[p].tag!=1){
			update(t[p].l,t[p].tag);
			update(t[p].r,t[p].tag);
			t[p].tag=1;
		}
	}
	void Insert(int x,int y,int &p,int l,int r){
		if(!p){p=++tot;t[p].tag=1;}t[p].sum=mod(t[p].sum+y);
		if(l==r)return;int mid=(l+r)>>1;Pushdown(p);
		if(x<=mid)Insert(x,y,t[p].l,l,mid);
		if(x>mid)Insert(x,y,t[p].r,mid+1,r);
	}
	int Query(int x,int y,int p,int l,int r){
		if(y<l||x>r||!p)return 0;
		if(x<=l&&r<=y)return t[p].sum;
		int mid=(l+r)>>1;Pushdown(p);
		return mod(Query(x,y,t[p].l,l,mid)+Query(x,y,t[p].r,mid+1,r));
	}
	int Merge(int x,int y){
		if(!x||!y)return x|y;
		Pushdown(x);Pushdown(y);
		t[x].sum=mod(t[x].sum+t[y].sum);
		t[x].l=Merge(t[x].l,t[y].l);
		t[x].r=Merge(t[x].r,t[y].r);
		return x;
	}
}tree;
void DFS(int x,int fa){
	int sum=1;
	f[x]=(a[x]>=0);dis[x]=dis[fa]+a[x];
	tree.Insert(dis[x],1,Root[x],-Lim,Lim);
	if(!vis[x][dis[x]]){vis[x][dis[x]]=true;F[x].push_back(dis[x]);}
	for(auto y:G[x]){
		if(y==fa)continue;
		DFS(y,x);
		f[x]=1ll*f[x]*f[y]%Mod;
		int fx=Root[x],fy=Root[y];
		if(F[x].size()<F[y].size()){
			swap(F[x],F[y]);
			swap(vis[x],vis[y]);
			swap(Root[x],Root[y]);
		}
		for(auto val:F[y]){
			int sum1=tree.Query(val,val,Root[y],-Lim,Lim);
			int sum2=tree.Query(dis[x]+dis[fa]-val,Lim,Root[x],-Lim,Lim);
			//dis[x]+dis[y]-dis[lca]-dis[fa[lca]]>=0;lca=x;
			if(!vis[x][val]){vis[x][val]=true;F[x].push_back(val);}
			f[x]=mod(f[x]+1ll*sum1*sum2%Mod);
		}
		tree.update(fx,f[y]);tree.update(fy,sum);
		Root[x]=tree.Merge(Root[x],Root[y]);
		sum=1ll*sum*f[y]%Mod;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		G[x].push_back(y);
		G[y].push_back(x);
	}
	DFS(1,0);
	printf("%d",f[1]);
	return 0;
}