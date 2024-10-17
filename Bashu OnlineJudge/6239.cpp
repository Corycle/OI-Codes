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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,a[N],sum[N];
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
int mod(int x){return x>=Mod?x-Mod:x;}
struct Tree{int sum,tag;};
struct Segment_Tree{
	Tree t[N*4];
	void update(int p,int x){
		t[p].sum=1ll*t[p].sum*x%Mod;
		t[p].tag=1ll*t[p].tag*x%Mod;
	}
	void Pushdown(int p){
		if(t[p].tag!=1){
			update(p<<1,t[p].tag);
			update(p<<1|1,t[p].tag);
			t[p].tag=1;
		}
	}
	void Build(int p,int l,int r){
		t[p].tag=1;
		if(l==r){t[p].sum=sum[l];return;}
		int mid=(l+r)>>1;
		Build(lson);Build(rson);
		t[p].sum=mod(t[p<<1].sum+t[p<<1|1].sum);
	}
	void Update(int x,int y,int z,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,z);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,z,lson);Update(x,y,z,rson);
		t[p].sum=mod(t[p<<1].sum+t[p<<1|1].sum);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();sum[0]=1;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)sum[i]=1ll*sum[i-1]*a[i]%Mod;
	for(int i=1;i<n;i++)sum[i]=1ll*sum[i]*2%Mod*Pow(3,n-i-1)%Mod;
	tree.Build(1,1,n);
	while(m--){
		int x=read(),y=read();
		int dlt=1ll*y*Pow(a[x],Mod-2)%Mod;
		tree.Update(x,n,dlt,1,1,n);a[x]=y;
		printf("%d\n",tree.t[1].sum);
	}
	return 0;
}