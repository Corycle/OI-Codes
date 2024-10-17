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
const double eps=1e-5;
const ll N=1e4+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll cnt,vis[N],prime[N];
void Prepare(ll maxn){
	for(ll i=2;i<=maxn;i++){
		if(!vis[i])prime[++cnt]=i;
		for(ll j=1;j<=cnt&&i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
}
int main(){
//	freopen("A.in","r",stdin);
//	freopen("A.out","w",stdout);
	Prepare(1e4);
	ll T=read();
	while(T--){
		ll n=read(),ans=inf;
		for(ll i=1;i<=cnt&&prime[i]<=n;i++){
			if(n%prime[i]==0){
				ll sum=0;
				while(n%prime[i]==0){
					n/=prime[i];sum++;
				}
				ans=min(ans,sum);
				if(n==1||ans==1)break;
			}
		}
		if(n!=1&&ans!=1){
			double q4=pow(n,1.0/4.0);
			double q3=pow(n,1.0/3.0);
			double q2=pow(n,1.0/2.0);
			if(abs(round(q4)-q4)<eps)ans=min(ans,4ll);
			else if(abs(round(q3)-q3)<eps)ans=min(ans,3ll);
			else if(abs(round(q2)-q2)<eps)ans=min(ans,2ll);
			else ans=1;
		}
		printf("%lld\n",ans);
	}
	return 0;
}