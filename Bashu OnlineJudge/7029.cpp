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
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,C,K;
ll a[N],b[N];
bool Check0(ll x){
	ll num=0,sum=0;
	for(int i=1;i<=n;i++)b[i]=0;
	for(int i=1;i<=n;i++){
		sum-=b[i];
		ll tmp=max(a[i]-sum,0ll);
		num+=tmp;sum+=tmp;b[i+x+1]+=tmp;
		if(num>K)return false;
	}
	return true;
}
bool Check1(ll x){
	ll num=0,sum=0,dlt=0;
	for(int i=1;i<=n;i++)b[i]=0;
	for(int i=1;i<=n;i++){
		dlt-=b[i];sum-=dlt;
		ll tmp=(ll)(ceil((double)(max(a[i]-sum,0ll))/x));
		num+=tmp;dlt+=tmp;sum+=tmp*x;b[i+x+1]+=tmp;
		if(num>K)return false;
	}
	return true;
}
bool Check2(ll x){
	ll num=0,sum=0,dlt=0,ddlt=0;
	for(int i=1;i<=n;i++)b[i]=0;
	for(int i=1;i<=n;i++){
		ddlt-=b[i]*2;dlt-=ddlt+b[i];sum-=dlt;
		ll tmp=(ll)(ceil((double)(max(a[i]-sum,0ll))/(x*x)));
		num+=tmp;ddlt+=tmp*2;dlt+=tmp*(x*2+1);sum+=tmp*x*x;b[i+x+1]+=tmp;
		if(num>K)return false;
	}
	return true;
}
int main(){
//	freopen("dispersion.in","r",stdin);
//	freopen("dispersion.out","w",stdout);
	read();n=read();C=read();K=read();
	for(int i=1;i<=n;i++)a[i]=read();
	if(C==0&&Check0(0)){puts("0");return 0;}
	int l=1,r=1e6,ans=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(C==0){if(Check0(mid)){ans=mid;r=mid-1;}else l=mid+1;}
		if(C==1){if(Check1(mid)){ans=mid;r=mid-1;}else l=mid+1;}
		if(C==2){if(Check2(mid)){ans=mid;r=mid-1;}else l=mid+1;}
	}
	printf("%d\n",ans);
	return 0;
}