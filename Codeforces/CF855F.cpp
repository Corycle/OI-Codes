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
const int Lim=1e5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
struct Tree{ll sum;int tag[2],Min1,Min2,Max1,Max2,NumMin,NumMax;};
struct Segment_Tree{
	Tree t[N*4];
	void updateMax(int p,int v){t[p].sum-=1ll*t[p].NumMin*(v-t[p].Min1);t[p].Min1=v;}
	void updateMin(int p,int v){t[p].sum+=1ll*t[p].NumMax*(v-t[p].Max1);t[p].Max1=v;}
	void Pushup(int p){
		int l=p<<1,r=p<<1|1;
		t[p].sum=t[l].sum+t[r].sum;
		t[p].tag[0]=t[l].tag[0]&t[r].tag[0];
		t[p].tag[1]=t[l].tag[1]&t[r].tag[1];
		t[p].Min1=min(t[l].Min1,t[r].Min1);t[p].Min2=min(t[l].Min2,t[r].Min2);t[p].NumMax=0;
		t[p].Max1=max(t[l].Max1,t[r].Max1);t[p].Max2=max(t[l].Max2,t[r].Max2);t[p].NumMin=0;
		if(t[l].Min1!=t[p].Min1)t[p].Min2=min(t[p].Min2,t[l].Min1);else t[p].NumMin+=t[l].NumMin;
		if(t[r].Min1!=t[p].Min1)t[p].Min2=min(t[p].Min2,t[r].Min1);else t[p].NumMin+=t[r].NumMin;
		if(t[l].Max1!=t[p].Max1)t[p].Max2=max(t[p].Max2,t[l].Max1);else t[p].NumMax+=t[l].NumMax;
		if(t[r].Max1!=t[p].Max1)t[p].Max2=max(t[p].Max2,t[r].Max1);else t[p].NumMax+=t[r].NumMax;
	}
	void Pushdown(int p){
		int l=p<<1,r=p<<1|1;
		if(t[p].Max1<t[l].Max1)updateMin(l,t[p].Max1);
		if(t[p].Max1<t[r].Max1)updateMin(r,t[p].Max1);
		if(t[p].Min1>t[l].Min1)updateMax(l,t[p].Min1);
		if(t[p].Min1>t[r].Min1)updateMax(r,t[p].Min1);
	}
	void Build(int p,int l,int r){
		if(l==r){t[p].Min1=-inf;t[p].Max1=inf;return;}
		int mid=(l+r)>>1;Build(lson);Build(rson);Pushup(p);
	}
	void Update(int p){
		if(t[p].tag[0]&&t[p].tag[1]){
			t[p].NumMax=t[p].NumMin=1;
			t[p].sum=t[p].Max1-t[p].Min1;
		}
	}
	void Max(int x,int y,int v,int p,int l,int r){
		if(y<l||x>r||t[p].Min1>=v)return;
		if(x<=l&&r<=y&&t[p].Min2>v&&t[p].tag[0]){updateMax(p,v);return;}
		if(l==r){t[p].Min1=v;t[p].tag[0]=1;Update(p);return;}
		int mid=(l+r)>>1;Pushdown(p);Max(x,y,v,lson);Max(x,y,v,rson);Pushup(p);
	}
	void Min(int x,int y,int v,int p,int l,int r){
		if(y<l||x>r||t[p].Max1<=v)return;
		if(x<=l&&r<=y&&t[p].Max2<v&&t[p].tag[1]){updateMin(p,v);return;}
		if(l==r){t[p].Max1=v;t[p].tag[1]=1;Update(p);return;}
		int mid=(l+r)>>1;Pushdown(p);Min(x,y,v,lson);Min(x,y,v,rson);Pushup(p);
	}
	ll Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].sum;
		int mid=(l+r)>>1;Pushdown(p);
		return Query(x,y,lson)+Query(x,y,rson);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	tree.Build(1,1,Lim);
	for(int i=1;i<=n;i++){
		int op=read(),l=read(),r=read()-1;
		if(op==1){
			int x=read();
			if(x<0)tree.Max(l,r,x,1,1,Lim);
			if(x>0)tree.Min(l,r,x,1,1,Lim);
		}
		if(op==2)printf("%lld\n",tree.Query(l,r,1,1,Lim));
	}
	return 0;
}
