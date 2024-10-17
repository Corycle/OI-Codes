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
#define ld long double
#define ull unsigned ll
using namespace std;
const int inf=0x3f3f3f3f;
const ll INV6=833333345000000041ll;
const ll MOD=1000000014000000049ll;
const int Mod=1e9+7;
const int N=1e7+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,a,Ans,P[100],Num[100];
int cnt,tot,mu[N],vis[N],prime[N];
ll mod(ll x){return x>=MOD?x-MOD:x;}
ll Multi(ll x,ll y){return ((ull)x*y-(ull)((ld)x/MOD*y)*MOD+MOD)%MOD;}
ll Pow1(ll x,ll y){ll ans=1;while(y){if(y&1)ans=Multi(ans,x);x=Multi(x,x);y>>=1;}return ans;}
ll Pow2(int x,int y){ll ans=1;while(y){if(y&1)ans=1ll*ans*x%Mod;x=1ll*x*x%Mod;y>>=1;}return ans;}
void Prepare(int maxn){
	mu[1]=1;
	for(int i=2;i<=maxn;i++){
		if(!vis[i]){prime[++cnt]=i;mu[i]=-1;}
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j])mu[i*prime[j]]=-mu[i];
			else{mu[i*prime[j]]=0;break;}
		}
	}
	for(int i=1;i<=maxn;i++)mu[i]+=mu[i-1];
}
ll Calc(ll n){
	ll S1=1,S2=0,S3=0;
	for(int i=1,j=0;i<=n;i=j+1){
		j=n/(n/i);
		ll t2=Multi(n/i,n/i),t3=Multi(t2,n/i);
		S2=mod(S2+Multi(t2,mod(mu[j]-mu[i-1]+MOD)));
		S3=mod(S3+Multi(t3,mod(mu[j]-mu[i-1]+MOD)));
	}
	return Multi(mod(mod(S3+Multi(S2,3))+S1*2),INV6);
}
void Divide(ll n){
	tot=0;
	for(int i=1;i<=cnt&&1ll*prime[i]*prime[i]<=n;i++){
		if(n%prime[i]==0){
			P[++tot]=prime[i];Num[tot]=0;
			while(n%prime[i]==0){Num[tot]++;n/=prime[i];}
		}
	}
	if(n!=1){P[++tot]=n;Num[tot]=1;}
}
ll F(ll n){return mod(Pow1(m-1,n)+Multi(m-1,(n&1)?MOD-1:1));}
void DFS(int x,ll d,ll Phi){
	if(x==tot+1){Ans=mod(Ans+Multi(Phi,F(n/d)));return;}
	DFS(x+1,d,Phi);
	d*=P[x];Phi*=P[x]-1;DFS(x+1,d,Phi);
	for(int i=2;i<=Num[x];i++){
		d*=P[x];Phi*=P[x];DFS(x+1,d,Phi);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();Prepare(1e7);
	while(T--){
		n=read();a=read();Ans=0;
		m=Calc(a);Divide(n);DFS(1,1,1);
		if(n%Mod==0)Ans=(Ans/Mod)*Pow2(n/Mod,Mod-2)%Mod;
		else Ans=(Ans%Mod)*Pow2(n%Mod,Mod-2)%Mod;
		printf("%lld\n",Ans);
	}
	return 0;
}