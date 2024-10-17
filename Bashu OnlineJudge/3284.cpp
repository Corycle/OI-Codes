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
const ll N=105;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,P,Ans;
ll Inv[N],inv[N],fac[N];
ll cnt[N],GCD[N][N],t[N];
ll gcd(ll x,ll y){
	return y==0?x:gcd(y,x%y);
}
ll Pow(ll x,ll y){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=(ans*tot)%P;
		tot=(tot*tot)%P;
		y>>=1;
	}
	return ans;
}
void Solve(){
	ll ans=fac[n];
	ll sum=0,tot=0;
	for(ll i=1;i<=n;i++){
		ans=(ans*Inv[cnt[i]])%P;
		for(ll j=1;j<=cnt[i];j++){
			ans=(ans*inv[i])%P;
			t[++tot]=i;
		}
	}
	for(ll i=1;i<=tot;i++){
		sum+=t[i]/2;
		for(ll j=i+1;j<=tot;j++){
			sum+=GCD[t[i]][t[j]];
		}
	}
	ans=ans*Pow(m,sum)%P;
	Ans=(Ans+ans)%P;
}
void DFS(ll x,ll sum){
	if(x==1){
		cnt[x]=n-sum;
		Solve();
		return;
	}
	for(ll i=0;sum+x*i<=n;i++){
		cnt[x]=i;
		DFS(x-1,sum+x*i);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();P=read();
	Inv[1]=inv[1]=fac[1]=Inv[0]=inv[0]=fac[0]=1;
	for(ll i=2;i<=n;i++)fac[i]=fac[i-1]*i%P;
	for(ll i=2;i<=n;i++)inv[i]=inv[P%i]*(P-P/i)%P;
	for(ll i=2;i<=n;i++)Inv[i]=Inv[i-1]*inv[i]%P;
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=n;j++){
			GCD[i][j]=gcd(i,j);
		}
	}
	DFS(n,0);
	printf("%lld",Ans*Inv[n]%P);
	return 0;
}