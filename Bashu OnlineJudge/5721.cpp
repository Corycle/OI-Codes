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
const double Pi=acos(-1);
const ll Mod=998244353;
const ll N=4000005;
const ll g=3;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
ll R[N],A[N],B[N],Ans[N];
ll Pow(ll x,ll y){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=(ans*tot)%Mod;
		tot=(tot*tot)%Mod;
		y>>=1;
	}
	return ans;
}
void NTT(ll a[],ll n,ll f){
	for(ll i=0;i<n;i++)if(i<R[i])swap(a[i],a[R[i]]);
	for(ll i=1;i<n;i<<=1){
		ll Wn=Pow(g,Mod-1+f*(Mod-1)/(i<<1));
		for(ll j=0;j<n;j+=(i<<1)){
			ll W=1;
			for(ll k=0;k<i;k++){
				ll x=a[j+k],y=W*a[j+k+i]%Mod;
				a[j+k]=(x+y)%Mod;a[j+k+i]=(x-y+Mod)%Mod;
				W=(W*Wn)%Mod;
			}
		}
	}
	if(f==-1){
		ll inv=Pow(n,Mod-2);
		for(ll i=0;i<n;i++)a[i]=(a[i]*inv)%Mod;
	}
}
int main(){
//	freopen("game.in","r",stdin);
//	freopen("game.out","w",stdout);
	scanf("%s",s);
	ll n=strlen(s),len=1,L=0;
	while(len<=n+n){len<<=1;L++;}
	for(ll i=0;i<len;i++){
		R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
	}
	for(ll i=0;i<n;i++){
		A[i]=(s[i]=='0');
		B[i]=(s[n-i-1]=='1');
	}
	NTT(A,len,1);NTT(B,len,1);
	for(ll i=0;i<len;i++)Ans[i]=A[i]*B[i]%Mod;
	NTT(Ans,len,-1);
	ll ans=n*n;
	for(ll i=1;i<n;i++){
		ll flag=1;
		for(ll j=i;j<n;j+=i){
			if(Ans[n-j-1]|Ans[n+j-1]){
				flag=0;break;
			}
		}
		ans^=flag*(n-i)*(n-i);
	}
	printf("%lld",ans);
	return 0;
}