/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
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
const ll N=2000005;
const ll M=105;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m;
vector<ll>f[M];
int main(){
//	freopen("floor.in","r",stdin);
//	freopen("floor.out","w",stdout);
	n=2e6;
	for(ll i=1;i<=n;i++)f[0].push_back(0);
	for(ll j=1;j<=64;j++){
		f[j].push_back(0);
		for(ll i=1;i<=n;i++){
			f[j].push_back(f[j][i-1]+f[j-1][i-1]+1);
			if(f[j][i]>1e18)break;
		}
	}
	ll T=read();
	while(T--){
		n=read();m=read();
		if(m==1)printf("%lld\n",n);
		else if(m==2){
			ll x=sqrt(2*n);
			if(x*(x+1)<2*n)x++;
			printf("%lld\n",x);
		}
		else{
			ll x=upper_bound(f[m].begin(),f[m].end(),n)-f[m].begin();
			if(f[m][x-1]==n)x--;printf("%lld\n",x);
		}
	}
	return 0;
}