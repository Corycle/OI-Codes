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
const ll inf=0x3f3f3f3f;
const ll M=1000005;
const ll N=300005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,Ans,sum1[M],sum2[M];
ll a[N],b[N],cnt1[N],cnt2[N];
void Divide(ll l,ll r){
	if(l==r)return;
	ll mid=(l+r)>>1;
	Divide(l,mid);Divide(mid+1,r);
	cnt1[mid]=cnt2[mid]=0;
	ll pos=mid,tot=0,Max1=0,Max2=0;
	for(ll i=mid+1;i<=r;i++){
		Max1=max(Max1,a[i]);
		cnt1[i]=(cnt1[i-1]+b[i])%m;
		cnt2[i]=(cnt1[i]-Max1%m+m)%m;
		sum2[cnt2[i]]++;
	}
	Max1=0;
	for(ll i=mid;i>=l;i--){
		Max1=max(Max1,a[i]);
		while(pos<r&&max(a[pos+1],Max2)<=Max1){
			pos++;
			Max2=max(Max2,a[pos]);
			sum1[cnt1[pos]]++;
			sum2[cnt2[pos]]--;
		}
		tot=(tot+b[i])%m;
		Ans+=sum1[(m-tot+m+Max1%m)%m];
		Ans+=sum2[(m-tot+m)%m];
	}
	for(ll i=mid+1;i<=pos;i++)sum1[cnt1[i]]--;
	for(ll i=pos+1;i<=r;i++)sum2[cnt2[i]]--;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=n;i++)a[i]=read();
	for(ll i=1;i<=n;i++)b[i]=a[i]%m;
	Divide(1,n);
	printf("%lld",Ans);
	return 0;
}