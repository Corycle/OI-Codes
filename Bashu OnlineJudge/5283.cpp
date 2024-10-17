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
const int N=5e6+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
bool vis[N];
map<ll,ll>Summu,Sumphi;
int n,m,cnt,prime[N];
ll mu[N],phi[N],Mu[N],Phi[N];
void Prepare(int maxn){
	mu[1]=phi[1]=1;
	for(int i=2;i<=maxn;i++){
		if(!vis[i]){prime[++cnt]=i;mu[i]=-1;phi[i]=i-1;}
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]){
				mu[i*prime[j]]=-mu[i];
				phi[i*prime[j]]=phi[i]*phi[prime[j]];
			}
			else{
				mu[i*prime[j]]=0;
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
		}
	}
	for(int i=1;i<=maxn;i++){mu[i]+=mu[i-1];phi[i]+=phi[i-1];}
}
ll SumPhi(ll n){
	if(n<=5e6)return phi[n];
	if(Sumphi[n])return Sumphi[n];
	ll ans=n*(1+n)/2;
	for(ll i=2,j=0;i<=n;i=j+1){
		j=n/(n/i);
		ans-=(j-i+1)*SumPhi(n/i);
	}
	return Sumphi[n]=ans;
}
ll SumMu(ll n){
	if(n<=5e6)return mu[n];
	if(Summu[n])return Summu[n];
	ll ans=1;
	for(ll i=2,j=0;i<=n;i=j+1){
		j=n/(n/i);
		ans-=(j-i+1)*SumMu(n/i);
	}
	return Summu[n]=ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();Prepare(5e6);
	while(T--){
		n=read();
		printf("%lld %lld\n",SumPhi(n),SumMu(n));
	}
	return 0;
}