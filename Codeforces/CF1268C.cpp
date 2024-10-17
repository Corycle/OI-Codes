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
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
int n,m,a[N];
struct Tree{
	ll c[N];
	int lowbit(int x){return x&(-x);}
	void Add(int x,int y){for(;x<=n;x+=lowbit(x))c[x]+=y;}
	ll Ask(int x){ll ans=0;for(;x>=1;x-=lowbit(x))ans+=c[x];return ans;}
	ll Query(int l,int r){return Ask(r)-Ask(l-1);}
}t1,t2;
ll Sum(int x){return 1ll*x*(x+1)/2;}
ll GetAns(int L,int R,int k){
	int l=L,r=R,pos=0,p=(1+k)>>1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(t1.Ask(mid)>=p){pos=mid;r=mid-1;}
		else l=mid+1;
	}
	ll v1=(Sum(p)+1ll*(pos-p)*p)-t2.Query(L,pos);
	ll v2=t2.Query(pos+1,R)-(Sum(k-p)+1ll*pos*(k-p));
	return v1+v2;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[read()]=i;
	for(int i=1,Min=n,Max=1;i<=n;i++){
		Max=max(Max,a[i]);Min=min(Min,a[i]);
		Ans+=t1.Query(a[i],n);
		t1.Add(a[i],1);t2.Add(a[i],a[i]);
		printf("%lld ",Ans+GetAns(Min,Max,i));
	}
	return 0;
}
