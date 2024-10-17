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
const ll inf=0x3f3f3f3f;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll c1,c2,e1,e2,Mod;
void Exgcd(ll a,ll b,ll &x,ll &y){
	if(!b)x=1;
	else{
		Exgcd(b,a%b,x,y);
		ll k=x;x=y;y=k-a/b*y;
	}
}
ll Pow(ll x,ll y){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=(__int128)ans*tot%Mod;
		tot=(__int128)tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	ll T=read();
	while(T--){
		c1=read();c2=read(),e1=read(),e2=read();Mod=read();
		ll x=0,y=0,a=0,b=0;Exgcd(e1,e2,x,y);
		if(x<0){x=-x;Exgcd(c1,Mod,a,b);c1=(a%Mod+Mod)%Mod;}//c1^x=Inv(c1)^(-x)
		if(y<0){y=-y;Exgcd(c2,Mod,a,b);c2=(a%Mod+Mod)%Mod;}//c2^y=Inv(c2)^(-y)
		printf("%lld\n",(ll)((__int128)Pow(c1,x)*Pow(c2,y)%Mod));
	}
	return 0;
}