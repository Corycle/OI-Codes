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
const ll INF=1e18;
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
ll Mod,Val,a[N];
struct Tree{int num,len;ll sum;vector<ll>F;};
struct Segment_Tree{
	Tree t[N*4];
	void Pushup(int p){
		int L=p<<1,R=p<<1|1;
		t[p].sum=t[L].sum+t[R].sum;
		for(int x=0,y=1;x<=t[L].num;x++){
			if(y!=0)y--;
			while(y<=t[R].num){
				if(t[L].F[x+1]-1-x*Mod+t[L].sum<t[R].F[y]){if(y!=0)y--;break;}
				t[p].F[x+y]=min(t[p].F[x+y],max(t[L].F[x],t[R].F[y]+x*Mod-t[L].sum));
				y++;
			}
		}
	}
	void Solve(int p){
		int l=0,r=t[p].num+1,ans=0;
		while(l<=r){
			int mid=(l+r)>>1;
			if(Val>=t[p].F[mid]){ans=mid;l=mid+1;}
			else r=mid-1;
		}
		Val=Val+t[p].sum-ans*Mod;
	}
	void Build(int p,int l,int r){
		t[p].num=r-l+1;t[p].F.push_back(-INF);
		for(int i=1;i<=t[p].num+1;i++)t[p].F.push_back(INF);
		if(l==r){t[p].sum=a[l];t[p].F[1]=Mod-a[l];return;}
		int mid=(l+r)>>1;Build(lson);Build(rson);Pushup(p);
	}
	void Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){Solve(p);return;}
		int mid=(l+r)>>1;Query(x,y,lson);Query(x,y,rson);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Mod=read();
	for(int i=1;i<=n;i++)a[i]=read();
	tree.Build(1,1,n);
	while(m--){
		int l=read(),r=read();Val=0;
		tree.Query(l,r,1,1,n);
		printf("%lld\n",Val);
	}
	return 0;
}
