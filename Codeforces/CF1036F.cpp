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
using namespace std;
const int inf=0x3f3f3f3f;
const int N=105;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int cnt,mu[N],vis[N],prime[N];
ld Pow(ld x,ll y){ld ans=1;while(y){if(y&1)ans=ans*x;x=x*x;y>>=1;}return ans;}
void Prepare(){
	mu[1]=1;
	for(int i=2;i<N;i++){
		if(!vis[i]){mu[i]=-1;prime[++cnt]=i;}
		for(int j=1;j<=cnt&&i*prime[j]<N;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j])mu[i*prime[j]]=-mu[i];
			else{mu[i*prime[j]]=0;break;}
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int Case=read();Prepare();
	while(Case--){
		ll n=read(),ans=0;
		for(int i=1;i<=60;i++){
			ll tmp=(ll)(pow(n,(ld)(1)/i))+1;
			while(Pow(tmp,i)>n)tmp--;
			ans+=mu[i]*(tmp-1);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
