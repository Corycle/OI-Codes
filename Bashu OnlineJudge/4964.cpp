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
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll A,B,C,n,m;
ll a[N],b[N];
ll Calc(ll Max){
	ll Sum1=0,Sum2=0;
	for(ll i=1;i<=m;i++){
		if(b[i]<Max)Sum1+=Max-b[i];
		if(b[i]>Max)Sum2+=b[i]-Max;
	}
	if(A>=B)return Sum2*B;
	return min(Sum1,Sum2)*A+(Sum2-min(Sum1,Sum2))*B;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	A=read();B=read();C=read();n=read();m=read();
	for(ll i=1;i<=n;i++)a[i]=read();
	for(ll i=1;i<=m;i++)b[i]=read();
	sort(a+1,a+n+1);sort(b+1,b+m+1);
	if(C==1e16){
		printf("%lld",Calc(a[1]));
		return 0;
	}
	ll l=0,r=inf,Ans=1e16;
	while(r-l>5){
		ll mid1=l+(r-l)/3;
		ll mid2=r-(r-l)/3;
		ll Sum1=Calc(mid1);
		ll Sum2=Calc(mid2);
		for(ll i=1;i<=n;i++)if(a[i]<mid1)Sum1+=C*(mid1-a[i]);
		for(ll i=1;i<=n;i++)if(a[i]<mid2)Sum2+=C*(mid2-a[i]);
		if(Sum1<Sum2)r=mid2;else l=mid1;
	}
	for(ll i=l;i<=r;i++){
		ll Sum=Calc(i);
		for(ll j=1;j<=n;j++){
			if(a[j]<i)Sum+=C*(i-a[j]);
		}
		Ans=min(Ans,Sum);
	}
	printf("%lld",Ans);
	return 0;
}