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
const int Mod=1e9+7;
const int N=50005;
const int M=32;
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

struct Base{
	int sum,a[M];
	void Insert(int x){
		if(!x)return;
		for(int i=30;i>=0;i--){
			if(!((x>>i)&1))continue;
			if(a[i])x^=a[i];
			else{
				a[i]=x;
				for(int j=i-1;j>=0;j--)if((a[i]>>j)&1)a[i]^=a[j];
				for(int j=i+1;j<=30;j++)if((a[j]>>i)&1)a[j]^=a[i];
				return;
			}
		}
	}
	void Init(int x){
		memset(a,0,sizeof(a));
		sum=x;Insert(x);
	}
	friend Base operator+(Base A,Base B){
		A.sum|=B.sum;
		for(int i=30;i>=0;i--){
			if(B.a[i])A.Insert(B.a[i]);
		}
		return A;
	}
};

Base Ans;
int n,m,a[N];
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
struct Segment_Tree{
	Base t[N*4];
	int tag[N*4];
	void Pushdown(int p){
		if(tag[p]!=-1){
			tag[p<<1]=tag[p];
			tag[p<<1|1]=tag[p];
			t[p<<1].Init(tag[p]);
			t[p<<1|1].Init(tag[p]);
			tag[p]=-1;
		}
	}
	void Build(int p,int l,int r){
		tag[p]=-1;
		if(l==r){t[p].Init(a[l]);return;}
		int mid=(l+r)>>1;
		Build(lson);Build(rson);
		t[p]=t[p<<1]+t[p<<1|1];
	}
	void Change(int x,int y,int z,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){
			t[p].Init(z);tag[p]=z;
			return;
		}
		int mid=(l+r)>>1;Pushdown(p);
		Change(x,y,z,lson);Change(x,y,z,rson);
		t[p]=t[p<<1]+t[p<<1|1];
	}
	void Query1(int x,int y,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){Ans=Ans+t[p];return;}
		int mid=(l+r)>>1;Pushdown(p);
		Query1(x,y,lson);Query1(x,y,rson);
	}
	int Query2(int x,int y,int p,int l,int r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y){
			return t[p].sum;
		}
		int mid=(l+r)>>1;Pushdown(p);
		return Query2(x,y,lson)|Query2(x,y,rson);
	}
}tree;
int Query1(int l,int r,int k){
	Ans.Init(0);
	tree.Query1(l,r,1,1,n);
	int num=0,ans=0;
	for(int i=0;i<=30;i++){
		if(Ans.a[i]){
			if((k>>num)&1)ans^=Ans.a[i];
			num++;
		}
	}
	if(k>=(1<<num))return -1;
	return ans;
}
int Query2(int l,int r){
	int ans=tree.Query2(l,r,1,1,n);
	return 1ll*ans%Mod*Pow(2,r-l)%Mod;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	tree.Build(1,1,n);
	while(m--){
		int op=read(),l=read(),r=read();
		if(op==1)tree.Change(l,r,read(),1,1,n);
		if(op==2)printf("%d\n",Query1(l,r,read()));
		if(op==3)printf("%d\n",Query2(l,r));
	}
	return 0;
}