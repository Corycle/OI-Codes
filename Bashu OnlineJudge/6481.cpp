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
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans,a[N],b[N],lst[N];
inline int mod(int x){return x>=Mod?x-Mod:x;}
struct Tree{int sum2,sum1,tag;};
struct Segment_Tree{
	Tree t[N*4];
	void update(int p,int num,int val){
		t[p].sum2=mod(t[p].sum2+1ll*val*mod(2ll*t[p].sum1%Mod+1ll*val*num%Mod)%Mod);
		t[p].sum1=mod(t[p].sum1+1ll*val*num%Mod);
		t[p].tag=mod(t[p].tag+val);
	}
	void Update(int x,int y,int val,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,r-l+1,val);return;}
		int mid=(l+r)>>1;
		if(t[p].tag){
			update(p<<1,mid-l+1,t[p].tag);
			update(p<<1|1,r-mid,t[p].tag);
			t[p].tag=0;
		}
		Update(x,y,val,lson);Update(x,y,val,rson);
		t[p].sum1=mod(t[p<<1].sum1+t[p<<1|1].sum1);
		t[p].sum2=mod(t[p<<1].sum2+t[p<<1|1].sum2);
	}
}tree;
int main(){
//	freopen("sequence.in","r",stdin);
//	freopen("sequence.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=b[i]=read();
	sort(b+1,b+n+1);m=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(b+1,b+m+1,a[i])-b;
		tree.Update(lst[a[i]]+1,i,1,1,1,n);
		Ans=mod(Ans+tree.t[1].sum2);
		lst[a[i]]=i;
	}
	printf("%d",Ans);
	return 0;
}