/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll Mod=1e9+7;
const ll N=10005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,k,p[N],f[N];
ll Pow(ll x,ll y){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=ans*tot%Mod;
		tot=tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
void Divide(ll n){
	for(ll i=1;i*i<=n;i++){
		if(n%i==0){
			p[++p[0]]=i;
			if(i*i!=n)p[++p[0]]=n/i;
		}
	}
	sort(p+1,p+p[0]+1);
}
int main(){
//	freopen("string.in","r",stdin);
//	freopen("string.out","w",stdout);
	n=read();k=read();
	Divide(n);
	ll ans=0;
	for(ll i=1;i<=p[0];i++){
		f[i]=Pow(k,p[i]);
		for(ll j=1;j<i;j++){
			if(p[i]%p[j]==0){
				f[i]=(f[i]-f[j]+Mod)%Mod;
			}
		}
		ans=(ans+f[i]*p[i]%Mod+Mod)%Mod;
	}
	printf("%lld",ans);
	return 0;
}