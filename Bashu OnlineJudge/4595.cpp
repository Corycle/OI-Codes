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
const ll Mod=2147483648ll;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll a[100005];
ll Multi(ll x,ll y,ll mod){
	ll ans=0,tot=x;
	while(y){
		if(y&1)ans=(ans+tot)%mod;
		tot=(tot+tot)%mod;
		y/=2;
	}
	return ans;
}
ll Pow(ll x,ll y,ll mod){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=(ans*tot)%mod;
		tot=(tot*tot)%mod;
		y/=2;
	}
	return ans;
}
int Miller_Rabin(ll n){
	if(n==2)return 1;
	if(n<2||!(n&1))return 0;
	int k=0,cnt=2;
	ll m=n-1;
	while(!(m&1)){
		k++;m>>=1;
	}
	for(int i=1;i<=cnt;i++){
		ll a=rand()%(n-1)+1;
		ll x=Pow(a,m,n),y=0;
		for(int j=1;j<=k;j++){
			y=(x*x)%n;
			if(y==1&&x!=1&&x!=n-1)return 0;
			x=y;
		}
		if(y!=1)return 0;
	}
	return 1;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	srand(time(NULL));
	a[1]=read();
	for(int i=1;i<=100000;i++){
		if(i!=1)a[i]=(a[i-1]+1234567890)%Mod;
		printf("%d",Miller_Rabin(a[i]));
	}
	return 0;
}