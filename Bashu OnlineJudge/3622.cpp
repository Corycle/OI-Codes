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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
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
		tot=Multi(tot,tot,mod);
		y/=2;
	}
	return ans;
}
bool Miller_Rabin(ll n){
	if(n==2)return true;
	if(n<2||!(n&1))return false;
	int k=0,cnt=5;
	ll m=n-1;
	while(!(m&1)){
		k++;m>>=1;
	}
	for(int i=1;i<=cnt;i++){
		ll a=rand()%(n-1)+1;
		ll x=Pow(a,m,n),y=0;
		for(int j=1;j<=k;j++){
			y=Multi(x,x,n);
			if(y==1&&x!=1&&x!=n-1)return false;
			x=y;
		}
		if(y!=1)return false;
	}
	return true;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	srand(time(NULL));
	while(1){
		ll p=read(),a=read();
		if(p+a==0)break;
		if(Miller_Rabin(p))printf("no\n");
		else if(Pow(a,p,p)==a)printf("yes\n");
		else printf("no\n");
	}
	return 0;
}