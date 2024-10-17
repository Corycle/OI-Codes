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
const ll Mod=1e8+7;
const ll N=5005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,k;
ll a[N][N];
ll Pow(ll x,ll y){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=(ans*tot)%Mod;
		tot=(tot*tot)%Mod;
		y>>=1;
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();k=read();
	ll mid=(n+1)/2;
	for(ll i=1;i<=m;i++){
		ll x=read()+1;
		ll y=read()+1;
		if(x>mid)x=n-x+1;
		if(y>mid)y=n-y+1;
		a[x][y]=1;a[y][x]=1;
	}
	ll sum=(1+mid)*mid/2;
	for(ll i=1;i<=mid;i++){
		for(ll j=1;j<=i;j++){
			if(a[i][j])sum--;
		}
	}
	printf("%lld",Pow(k,sum));
	return 0;
}