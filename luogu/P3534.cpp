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
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,a[N],b[N],sum[N];
ll Sum(ll x){return x*(x+1)/2;}
int Check(int dlt){
	ll num=m;
	for(int i=1;i<=n;i++)a[i]=b[i];
	for(int i=1;i<=n-1;i++)if(a[i+1]>a[i]+dlt){num-=a[i+1]-(a[i]+dlt);a[i+1]=a[i]+dlt;}
	for(int i=n-1;i>=1;i--)if(a[i]>a[i+1]+dlt){num-=a[i]-(a[i+1]+dlt);a[i]=a[i+1]+dlt;}
	if(num<0)return 0;
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+a[i];
	for(int i=1,l=1,r=1;i<=n;i++){
		int x=a[i];
		a[i]=0;
		while(l<i&&a[l]<(i-l)*dlt)l++;
		while(r<n&&a[r+1]>=(r-i+1)*dlt)r++;
		if(sum[r]-sum[l-1]-num<=(Sum(i-l)+Sum(r-i))*dlt)return i;
		a[i]=x;
	}
	return 0;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)b[i]=read();
	int l=0,r=1e9,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(Check(mid)){ans=mid;r=mid-1;}
		else l=mid+1;
	}
	printf("%d %d\n",Check(ans),ans);
	return 0;
}
