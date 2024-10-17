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
#define pii pair<int,int>
#define fst first
#define scd second
#define mp make_pair
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
int Ans[N];
vector<pii>G1[N],G2[N];
struct Node{int h,a,b;}P[N];
struct Tree{int m1,m2,tag;};
struct Segment_Tree{
	Tree t[N*4];
	void update(int p,int x){
		t[p].tag=max(t[p].tag,x);
		t[p].m2=max(t[p].m2,t[p].m1+t[p].tag);
	}
	void Pushdown(int p){
		if(t[p].tag!=-inf){
			update(p<<1,t[p].tag);
			update(p<<1|1,t[p].tag);
			t[p].tag=-inf;
		}
	}
	void Pushup(int p){
		t[p].m1=max(t[p<<1].m1,t[p<<1|1].m1);
		t[p].m2=max(t[p<<1].m2,t[p<<1|1].m2);
	}
	void Build(int p,int l,int r){
		t[p].m1=t[p].m2=t[p].tag=-inf;
		if(l==r)return;int mid=(l+r)>>1;
		Build(lson);Build(rson);Pushup(p);
	}
	void Change(int x,int val,int p,int l,int r){
		if(l==r){t[p].m1=val;t[p].tag=-inf;return;}
		int mid=(l+r)>>1;Pushdown(p);
		(x<=mid?Change(x,val,lson):Change(x,val,rson));Pushup(p);
	}
	void Update(int x,int y,int z,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,z);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,z,lson);Update(x,y,z,rson);Pushup(p);
	}
	int Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return -1;
		if(x<=l&&r<=y)return t[p].m2;
		int mid=(l+r)>>1;Pushdown(p);
		return max(Query(x,y,lson),Query(x,y,rson));
	}
}tree;
void Solve(){
	tree.Build(1,1,n);
	for(int i=1;i<=n;i++){
		for(auto tmp:G1[i]){
			if(tmp.scd==1)tree.Change(tmp.fst,P[tmp.fst].h,1,1,n);
			if(tmp.scd==-1)tree.Change(tmp.fst,-inf,1,1,n);
		}
		tree.Update(max(1,i-P[i].b),i-P[i].a,-P[i].h,1,1,n);
		for(auto tmp:G2[i]){
			Ans[tmp.fst]=max(Ans[tmp.fst],tree.Query(tmp.scd,i,1,1,n));
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		P[i].h=read();P[i].a=read();P[i].b=read();
		if(i+P[i].a<=n)G1[i+P[i].a].push_back(mp(i,1));
		if(i+P[i].b<n)G1[i+P[i].b+1].push_back(mp(i,-1));
	}
	m=read();
	for(int i=1;i<=m;i++){
		int l=read(),r=read();Ans[i]=-1;
		G2[r].push_back(mp(i,l));
	}
	Solve();
	for(int i=1;i<=n;i++)P[i].h=1e9-P[i].h;
	Solve();
	for(int i=1;i<=m;i++)printf("%d\n",Ans[i]);
	return 0;
}