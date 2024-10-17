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
const int Inv2=5e8+4;
const int Mod=1e9+7;
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,val[N];
int mod(int x){return x>=Mod?x-Mod:x;}
struct Tree{int sum,a,b,c,x0,x1,x2;};
struct Segment_Tree{
	Tree t[N*4];
	void Prepare(int p,int x){
		t[p].sum=val[x];
		t[p].x0=1;t[p].x1=x;
		t[p].x2=1ll*x*x%Mod;
	}
	void update(int a,int b,int c,int p){
		t[p].sum=mod(t[p].sum+1ll*a*t[p].x2%Mod);t[p].a=mod(t[p].a+a);
		t[p].sum=mod(t[p].sum+1ll*b*t[p].x1%Mod);t[p].b=mod(t[p].b+b);
		t[p].sum=mod(t[p].sum+1ll*c*t[p].x0%Mod);t[p].c=mod(t[p].c+c);
	}
	void Pushdown(int p){
		if(t[p].a||t[p].b||t[p].c){
			update(t[p].a,t[p].b,t[p].c,p<<1);
			update(t[p].a,t[p].b,t[p].c,p<<1|1);
			t[p].a=t[p].b=t[p].c=0;
		}
	}
	void Build(int p,int l,int r){
		if(l==r){Prepare(p,l);return;}
		int mid=(l+r)>>1;
		Build(lson);Build(rson);
		t[p].sum=mod(t[p<<1].sum+t[p<<1|1].sum);
		t[p].x0=mod(t[p<<1].x0+t[p<<1|1].x0);
		t[p].x1=mod(t[p<<1].x1+t[p<<1|1].x1);
		t[p].x2=mod(t[p<<1].x2+t[p<<1|1].x2);
	}
	void Update(int x,int y,int a,int b,int c,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(a,b,c,p);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,a,b,c,lson);Update(x,y,a,b,c,rson);
		t[p].sum=mod(t[p<<1].sum+t[p<<1|1].sum);
	}
	int Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].sum;
		int mid=(l+r)>>1;Pushdown(p);
		return mod(Query(x,y,lson)+Query(x,y,rson));
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)val[i]=read();
	for(int i=1;i<=n;i++)val[i]=mod(val[i-1]+val[i]);
	for(int i=1;i<=n;i++)val[i]=mod(val[i-1]+val[i]);
	tree.Build(1,1,n);
	while(m--){
		int op=read(),l=read(),r=read();
		if(l>r)swap(l,r);
		if(op==1){
			int d=read();
			int a1=1ll*d*Inv2%Mod;
			int b1=1ll*d*Inv2%Mod*mod(3-2*l%Mod+Mod)%Mod;
			int c1=1ll*d*Inv2%Mod*(l-1)%Mod*(l-2)%Mod;
			tree.Update(l,r,a1,b1,c1,1,1,n);
			if(r==n)continue;
			int a2=0;
			int b2=1ll*d*(r-l+1)%Mod;
			int c2=1ll*d*mod(1ll*(r-l+1)*(r-l+2)%Mod*Inv2%Mod-1ll*r*(r-l+1)%Mod+Mod)%Mod;
			tree.Update(r+1,n,a2,b2,c2,1,1,n);
		}
		if(op==2){
			int Ans=1ll*(r-l+1)*tree.Query(n,n,1,1,n)%Mod;
			Ans=mod(Ans-tree.Query(l-1,r-1,1,1,n)+Mod);
			Ans=mod(Ans-tree.Query(n-r,n-l,1,1,n)+Mod);
			printf("%d\n",Ans);
		}
	}
	return 0;
}