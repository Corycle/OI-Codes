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
const ll Mod=1e9+7;
const ll N=5005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,K;
ll s[N],c[N],t[N],g[N],f[N],Ans[N];
ll Pow(ll x,ll y){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=ans*tot%Mod;
		tot=tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
int main(){
//	freopen("poetry.in","r",stdin);
//	freopen("poetry.out","w",stdout);
	n=read();m=read();K=read();
	for(ll i=1;i<=n;i++){
		s[i]=read();
		c[i]=read();
	}
	char op[5];
	for(ll i=1;i<=m;i++){
		scanf("%s",op);
		t[(ll)(op[0]-'A'+1)]++;
	}
	g[0]=1;
	for(ll i=1;i<=K;i++){
		for(ll j=1;j<=n;j++){
			if(i>=s[j])g[i]=(g[i]+g[i-s[j]])%Mod;
		}
	}
	for(ll i=1;i<=n;i++){
		f[c[i]]=(f[c[i]]+g[K-s[i]])%Mod;
	}
	Ans[0]=1;
	for(ll i=1;i<=26;i++){
		if(!t[i]){
			Ans[i]=Ans[i-1];
			continue;
		}
		for(ll j=1;j<=n;j++){
			Ans[i]=(Ans[i]+Ans[i-1]*Pow(f[j],t[i])%Mod)%Mod;
		}
	}
	printf("%lld",Ans[26]);
	return 0;
}