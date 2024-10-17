/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int Mod=1e9+9;
const int N=500005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,a[N];
struct Node{int l,r;}P[N];
bool cmp(Node A,Node B){
	return A.l!=B.l?A.l<B.l:A.r<B.r;
}
int mod(int x){return x>=Mod?x-Mod:x;}
struct Segment_Tree{
	struct Tree{int tag,sum;}t[N*4];
	void update(int p,int x){
		t[p].tag=1ll*t[p].tag*x%Mod;
		t[p].sum=1ll*t[p].sum*x%Mod;
	}
	void Pushdown(int p){
		if(t[p].tag!=1){
			update(p<<1,t[p].tag);
			update(p<<1|1,t[p].tag);
			t[p].tag=1;
		}
	}
	void Add(int x,int y,int p,int l,int r){
		if(x<l||x>r)return;
		if(l==r){t[p].sum=mod(t[p].sum+y);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Add(x,y,lson);Add(x,y,rson);
		t[p].sum=mod(t[p<<1].sum+t[p<<1|1].sum);
	}
	void Update(int x,int y,int z,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,z);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,z,lson);Update(x,y,z,rson);
		t[p].sum=mod(t[p<<1].sum+t[p<<1|1].sum);
	}
	int Ask(int x,int y,int p,int l,int r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].sum;
		int mid=(l+r)>>1;Pushdown(p);
		return mod(Ask(x,y,lson)+Ask(x,y,rson));
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		P[i].l=read();
		P[i].r=read();
	}
	for(int i=1;i<=m;i++)a[i]=read();
	a[++m]=0;sort(a+1,a+m+1);m=unique(a+1,a+m+1)-a-1;
	for(int i=1;i<=n;i++){
		P[i].l=lower_bound(a+1,a+m+1,P[i].l)-a;
		P[i].r=upper_bound(a+1,a+m+1,P[i].r)-a-1;
	}
	int num=0;
	sort(P+1,P+n+1,cmp);
	tree.Add(1,1,1,1,m);
	for(int i=1;i<=n;i++){
		if(P[i].l<=P[i].r){
			int tmp=tree.Ask(max(P[i].l-1,1),P[i].r,1,1,m);
			tree.Add(P[i].r,tmp,1,1,m);
			if(P[i].r<m)tree.Update(P[i].r+1,m,2,1,1,m);
		}
		else num++;
	}
	int Ans=tree.Ask(m,m,1,1,m);
	while(num--)Ans=mod(Ans+Ans);
	printf("%d",Ans);
	return 0;
}