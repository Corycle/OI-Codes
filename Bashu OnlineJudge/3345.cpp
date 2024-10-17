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
const ll inf=0x3f3f3f3f;
const ll Mod=100000007;
const ll N=1000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m;
ll f[N];
ll Pow(ll x,ll y,ll mod){
	ll ans=1,tot=x%mod;
	while(y){
		if(y&1)ans=(ans*tot)%mod;
		tot=(tot*tot)%mod;
		y/=2;
	}
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	ll Base=Pow(2,n,Mod)-1;
	ll All=Base,tmp=2;
	for(ll i=3;i<=m;i++){
		tmp=tmp*i%Mod;//累计得m! 
		All=All*(Base-i+2)%Mod;
		f[i]=(All+Mod-f[i-1]+Mod-f[i-2]*(i-1)%Mod*(Base-(i-2)+Mod)%Mod)%Mod;
		//     总数  -  空集    -   重复 
	}
	printf("%lld",f[m]*Pow(tmp,Mod-2,Mod)%Mod);//f[m]*Inv(m!,Mod); ==> f[m]/(m!)
	return 0;
}