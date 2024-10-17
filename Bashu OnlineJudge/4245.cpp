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
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
int n,m,a[N];
struct Tree{int Max1,Max2,Min1,Min2,NumMax,NumMin;ll sum,tag;};
struct Segment_Tree{
	Tree t[N*4];
	void update(int p,int l,int r,ll val){
		t[p].Max1+=val;t[p].Max2+=val;
		t[p].Min1+=val;t[p].Min2+=val;
		t[p].sum+=1ll*val*(r-l+1);t[p].tag+=val;
	}
	void updateMax(int p,int val){
		if(t[p].Max1==t[p].Min1)t[p].Max1=val;
		if(t[p].Max2==t[p].Min1)t[p].Max2=val;
		t[p].sum+=1ll*t[p].NumMin*(val-t[p].Min1);t[p].Min1=val;
	}
	void updateMin(int p,int val){
		if(t[p].Min1==t[p].Max1)t[p].Min1=val;
		if(t[p].Min2==t[p].Max1)t[p].Min2=val;
		t[p].sum+=1ll*t[p].NumMax*(val-t[p].Max1);t[p].Max1=val;
	}
	void Pushup(int p){
		int l=p<<1,r=p<<1|1;
		t[p].sum=t[l].sum+t[r].sum;
		if(t[l].Max1>t[r].Max1){t[p].Max1=t[l].Max1;t[p].Max2=max(t[r].Max1,t[l].Max2);t[p].NumMax=t[l].NumMax;}
		if(t[l].Max1<t[r].Max1){t[p].Max1=t[r].Max1;t[p].Max2=max(t[l].Max1,t[r].Max2);t[p].NumMax=t[r].NumMax;}
		if(t[l].Max1==t[r].Max1){t[p].Max1=t[l].Max1;t[p].Max2=max(t[l].Max2,t[r].Max2);t[p].NumMax=t[l].NumMax+t[r].NumMax;}
		if(t[l].Min1<t[r].Min1){t[p].Min1=t[l].Min1;t[p].Min2=min(t[r].Min1,t[l].Min2);t[p].NumMin=t[l].NumMin;}
		if(t[l].Min1>t[r].Min1){t[p].Min1=t[r].Min1;t[p].Min2=min(t[l].Min1,t[r].Min2);t[p].NumMin=t[r].NumMin;}
		if(t[l].Min1==t[r].Min1){t[p].Min1=t[l].Min1;t[p].Min2=min(t[l].Min2,t[r].Min2);t[p].NumMin=t[l].NumMin+t[r].NumMin;}
	}
	void Pushdown(int p,int l,int r){
		int mid=(l+r)>>1;
		if(t[p].tag){update(lson,t[p].tag);update(rson,t[p].tag);t[p].tag=0;}
		if(t[p].Max1<t[p<<1].Max1)updateMin(p<<1,t[p].Max1);
		if(t[p].Min1>t[p<<1].Min1)updateMax(p<<1,t[p].Min1);
		if(t[p].Max1<t[p<<1|1].Max1)updateMin(p<<1|1,t[p].Max1);
		if(t[p].Min1>t[p<<1|1].Min1)updateMax(p<<1|1,t[p].Min1);
	}
	void Init(int p,int x){
		t[p].Max1=t[p].Min1=t[p].sum=x;
		t[p].Max2=-inf;t[p].Min2=inf;
		t[p].NumMax=t[p].NumMin=1;
	}
	void Build(int p,int l,int r){
		if(l==r){Init(p,a[l]);return;}
		int mid=(l+r)>>1;Build(lson);Build(rson);Pushup(p);
	}
	void Add(int x,int y,int val,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,l,r,val);return;}
		int mid=(l+r)>>1;Pushdown(p,l,r);
		Add(x,y,val,lson);Add(x,y,val,rson);Pushup(p);
	}
	void Max(int x,int y,int val,int p,int l,int r){
		if(y<l||x>r||t[p].Min1>=val)return;
		if(x<=l&&r<=y&&t[p].Min2>val){updateMax(p,val);return;}
		int mid=(l+r)>>1;Pushdown(p,l,r);
		Max(x,y,val,lson);Max(x,y,val,rson);Pushup(p);
	}
	void Min(int x,int y,int val,int p,int l,int r){
		if(y<l||x>r||t[p].Max1<=val)return;
		if(x<=l&&r<=y&&t[p].Max2<val){updateMin(p,val);return;}
		int mid=(l+r)>>1;Pushdown(p,l,r);
		Min(x,y,val,lson);Min(x,y,val,rson);Pushup(p);
	}
	ll Sum(int x,int y,int p,int l,int r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].sum;
		int mid=(l+r)>>1;Pushdown(p,l,r);
		return Sum(x,y,lson)+Sum(x,y,rson);
	}
	int GetMax(int x,int y,int p,int l,int r){
		if(y<l||x>r)return -inf;
		if(x<=l&&r<=y)return t[p].Max1;
		int mid=(l+r)>>1;Pushdown(p,l,r);
		return max(GetMax(x,y,lson),GetMax(x,y,rson));
	}
	int GetMin(int x,int y,int p,int l,int r){
		if(y<l||x>r)return inf;
		if(x<=l&&r<=y)return t[p].Min1;
		int mid=(l+r)>>1;Pushdown(p,l,r);
		return min(GetMin(x,y,lson),GetMin(x,y,rson));
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	tree.Build(1,1,n);
	m=read();
	while(m--){
		int op=read(),l=read(),r=read();
		if(op==1)tree.Add(l,r,read(),1,1,n);
		if(op==2)tree.Max(l,r,read(),1,1,n);
		if(op==3)tree.Min(l,r,read(),1,1,n);
		if(op==4)printf("%lld\n",tree.Sum(l,r,1,1,n));
		if(op==5)printf("%d\n",tree.GetMax(l,r,1,1,n));
		if(op==6)printf("%d\n",tree.GetMin(l,r,1,1,n));
	}
	return 0;
}