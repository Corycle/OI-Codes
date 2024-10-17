#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
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
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
map<ll,ll>Hash;
ll Pow(ll x,ll y,ll mod){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=(ans*tot)%mod;
		tot=(tot*tot)%mod;
		y/=2;
	}
	return ans;
}
ll BSGS(ll a,ll b,ll p){
	a%=p;b%=p;
	if(!a){
		if(!b)return 1;
		else return -1;
	}
	if(b==1){
		if(a)return 0;
		else return -1;
	}
	Hash.clear();
	ll m=ceil(sqrt(p)),tmp=1;
	Hash[1]=m+1;
	for(ll i=1;i<m;i++){
		tmp=tmp*a%p;
		if(!Hash[tmp])Hash[tmp]=i;
	}
	ll d=1;
	tmp=Pow(a,p-m-1,p);
	for(ll i=0;i<m;i++){
		ll j=Hash[b*d%p];
		if(j){
			if(j==m+1)j=0;
			return i*m+j;
		}
		d=d*tmp%p;
	}
	return -1;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	ll T=read();
	while(T--){
		ll a=read(),b=read(),p=read();
		ll ans=BSGS(a,b,p);
		if(ans!=-1)printf("%lld\n",ans);
		else printf("Orz, I cannot find x!\n");
	}
	return 0;
}