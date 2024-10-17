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
const int N=5e5+5;
const int M=55;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,K,Q,top;
int c[N],L[N],R[N],id[N],lst[N];
struct Node{int x,y,c;}E[N],st[N];
struct Union_Basis{
	int fa[N],sum[N],dis[N];
	int Find(int x){return x==fa[x]?x:Find(fa[x]);}
	int Dist(int x){return x==fa[x]?0:dis[x]^Dist(fa[x]);}
	void Init(){for(int i=1;i<=n;i++){fa[i]=i;sum[i]=1;}}
	void Delete(int x,int y){fa[x]=x;dis[x]=0;sum[y]-=sum[x];}
	void Merge(int x,int y,int c){
		int w=Dist(x)^Dist(y)^1;
		x=Find(x);y=Find(y);
		if(sum[x]>sum[y])swap(x,y);
		fa[x]=y;dis[x]=w;sum[y]+=sum[x];
		st[++top]=(Node){x,y,c};
	}
}F[M];
struct Segment_Tree{
	vector<int>t[N*4];
	void Reset(int tmp){
		while(top>tmp){
			int x=st[top].x,y=st[top].y,c=st[top].c;top--;
			F[c].Delete(x,y);
		}
	}
	void Insert(int x,int y,int id,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){t[p].push_back(id);return;}
		int mid=(l+r)>>1;Insert(x,y,id,lson);Insert(x,y,id,rson);
	}
	void Solve(int p,int l,int r){
		int tmp=top;
		for(auto id:t[p]){
			int x=E[id].x,y=E[id].y,c=E[id].c;
			if(c&&F[c].Find(x)!=F[c].Find(y))F[c].Merge(x,y,c);
		}
		if(l==r){
			int x=E[id[l]].x,y=E[id[l]].y;
			if(c[l]==E[id[l]].c||F[c[l]].Find(x)!=F[c[l]].Find(y)){puts("YES");E[id[l]].c=c[l];}
			else{
				if(F[c[l]].Dist(x)^F[c[l]].Dist(y)){puts("YES");E[id[l]].c=c[l];}
				else puts("NO");
			}
			Reset(tmp);
			return;
		}
		int mid=(l+r)>>1;Solve(lson);Solve(rson);Reset(tmp);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();K=read();Q=read();
	for(int i=1;i<=m;i++){E[i].x=read();E[i].y=read();}
	for(int i=1;i<=Q;i++){
		id[i]=read();c[i]=read();
		if(lst[id[i]])R[lst[id[i]]]=i;
		lst[id[i]]=i;L[i]=i+1;R[i]=Q;
	}
	for(int i=1;i<=Q;i++)if(L[i]<=R[i])tree.Insert(L[i],R[i],id[i],1,1,Q);
	for(int i=1;i<=K;i++)F[i].Init();
	tree.Solve(1,1,Q);
	return 0;
}
