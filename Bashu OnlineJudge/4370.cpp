#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const double Pi=acos(-1);
const ll N=300005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll R[N];
complex<double>A[N],B[N];
void FFT(complex<double>a[],ll n,ll f){
	for(ll i=0;i<n;i++)if(i<R[i])swap(a[i],a[R[i]]);
	for(ll i=1;i<n;i<<=1){
		complex<double>Wn(cos(Pi/i),f*sin(Pi/i));
		for(ll j=0;j<n;j+=(i<<1)){
			complex<double>W(1,0);
			for(ll k=0;k<i;k++){
				complex<double>x=a[j+k],y=W*a[j+k+i];
				a[j+k]=x+y;a[j+k+i]=x-y;W*=Wn;
			}
		}
	}
	if(f==-1)for(ll i=0;i<n;i++)a[i]/=n;
}
ll a[N],num[N],sum[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	ll T=read();
	while(T--){
		ll n=read(),m=0;
		memset(num,0,sizeof(num));
		memset(sum,0,sizeof(sum));
		for(ll i=0;i<n;i++){
			a[i]=read();
			num[a[i]]++;
			m=max(m,a[i]+1);
		}
		sort(a,a+n);
		ll len=1,L=0;
		while(len<m+m){len<<=1;L++;}
		for(ll i=0;i<len;i++){
			R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
		}
		for(ll i=0;i<len;i++)A[i]=B[i]=num[i];
		FFT(A,len,1);FFT(B,len,1);
		for(ll i=0;i<len;i++)A[i]*=B[i];
		FFT(A,len,-1);
		for(ll i=0;i<len;i++){
			sum[i]=(ll)(A[i].real()+0.5);
		}
		len=a[n-1]*2;
		for(ll i=0;i<n;i++)sum[a[i]+a[i]]--;
		for(ll i=1;i<=len;i++)sum[i]/=2;
		for(ll i=1;i<=len;i++)sum[i]=sum[i-1]+sum[i];
		double ans=0,tot=n*(n-1)*(n-2)/6;//总情况数 
		for(ll i=0;i<n;i++){
			ans+=(sum[len]-sum[a[i]]);//在剩下的n-1条边中选出两条边的长度和大于a[i] 
			ans-=(n-i-1)*i;//减掉一条边大于a[i],一条边小于a[i]的情况 
			ans-=(n-i-1)*(n-i-2)/2;//减掉两条边都大于a[i]的情况 
			ans-=(n-1);//减掉一条边为a[i]的情况 
		}
		printf("%.7lf\n",ans/tot);
	}
	return 0;
}