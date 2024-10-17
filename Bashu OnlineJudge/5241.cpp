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
const ll Mod=1e9+9;
const ll N=1050005;
const ll M=21;
inline ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll maxn;
inline void FST(ll a[][M],ll n,ll f){
	for(register ll i=1;i<maxn;i<<=1){
		for(register ll j=0;j<maxn;j++){
			if(i&j){
				for(register ll k=0;k<=n;k++){
					a[j][k]+=f*a[j-i][k];
				}
			}
		}
	}
	for(register ll i=0;i<maxn;i++){
		for(register ll j=0;j<=n;j++){
			a[i][j]%=Mod;
		}
	}
}
ll n,num[N];
ll a[N][M],b[N][M],c[N][M];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();maxn=(1<<n);
	for(register ll i=1;i<maxn;i++)num[i]=num[i-(i&-i)]+1;
	for(register ll i=0;i<maxn;i++)a[i][num[i]]=read();
	for(register ll i=0;i<maxn;i++)b[i][num[i]]=read();
	FST(a,n,1);FST(b,n,1);
	for(register ll i=0;i<maxn;i++){
		for(register ll j=0;j<=n;j++){
			for(register ll k=0;k<=j;k++){
				c[i][j]+=a[i][k]*b[i][j-k];
			}
			c[i][j]%=Mod;
		}
	}
	FST(c,n,-1);
	for(register ll i=0;i<maxn;i++){
		printf("%lld ",(c[i][num[i]]+Mod)%Mod);
	}
	return 0;
}