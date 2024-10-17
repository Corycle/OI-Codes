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
const int Mod=1e9+7;
const int N=500005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,Ans;
int p[N],mu[N],sum[N],vis[N],prime[N];
int mod(int x){return x>=Mod?x-Mod:x;}
int Sqr(int x){return 1ll*x*x%Mod;}
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
void Prepare(int maxn){
	mu[1]=1;
	for(int i=2;i<=maxn;i++){
		if(!vis[i]){prime[++cnt]=i;mu[i]=-1;}
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j])mu[i*prime[j]]=-mu[i];
			else{mu[i*prime[j]]=0;break;}
		}
		mu[i]=mod(mu[i]+Mod);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	Prepare(max(n,m));
	int Min=min(n,m),Max=max(n,m);
	for(int i=1;i<=Max;i++)p[i]=1;
	for(int d=1;d<=Min;d++){
		int ans=0;
		for(int i=1;i<=Max/d;i++){
			p[i]=1ll*p[i]*i%Mod;
			sum[i]=mod(sum[i-1]+p[i]);
		}
		for(int k=1;k<=Min/d;k++){
			ans=mod(ans+1ll*mu[k]*Sqr(p[k])%Mod*sum[n/(d*k)]%Mod*sum[m/(d*k)]%Mod);
		}
		Ans=mod(Ans+1ll*Pow(d,d)*ans%Mod);
	}
	printf("%d",Ans);
	return 0;
}