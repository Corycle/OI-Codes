#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int p=1000000007;
const int N=10000005;
const int M=5000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Pow(ll x,ll y,ll mod){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=(ans*tot)%mod;
		tot=(tot*tot)%mod;
		y>>=1;
	}
	return ans;
}
bool vis[N];
ll g[N],f[N];
int d,cnt,prime[M];
int sum1[N],sum2[N];
/*
	g[i]=∑(i-1,n) i^d
	f[i]=Inv(i!)
*/
void Prepare(){
	g[1]=1;
	for(int i=2;i<=d+2;i++){
		if(!vis[i]){
			prime[++cnt]=i;
			g[i]=Pow(i,d,p);
		}
		for(int j=1;j<=cnt;j++){
			if(1ll*i*prime[j]>d+2)break;
			vis[i*prime[j]]=1;
			g[i*prime[j]]=g[i]*g[prime[j]]%p;
			if(i%prime[j]==0)break;
		}
	}
	for(int i=2;i<=d+2;i++)g[i]=(g[i]+g[i-1])%p;
}
ll Lagrange(int x){
	ll ans=0;
	f[0]=f[1]=sum1[0]=sum2[d+3]=1;
	for(int i=2;i<=d+2;i++)f[i]=(p-p/i)*f[p%i]%p;
	for(int i=2;i<=d+2;i++)f[i]=f[i]*f[i-1]%p;
	for(int i=1;i<=d+2;i++)sum1[i]=1ll*sum1[i-1]*(x-i)%p;//前缀积 
	for(int i=d+2;i>=1;i--)sum2[i]=1ll*sum2[i+1]*(x-i)%p;//后缀积 
	for(int i=1;i<=d+2;i++){
		ll t1=1ll*sum1[i-1]*sum2[i+1]%p;
		ll t2=f[i-1]*f[d+2-i]%p;
		if((d+2-i)&1)t2=-t2;
		ans=(ans+t1*t2%p*g[i]%p)%p;
	}
	return (ans%p+p)%p;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int n=read();d=read();Prepare();
	if(n<=d+1)printf("%lld",g[n]);
	else printf("%lld",Lagrange(n));
	return 0;
}