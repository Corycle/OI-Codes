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
const ll N=1e6+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,tot;
ll a[N],b[N],f[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();f[0]=1;
	for(ll i=1;i<=n;i++)a[i]=read();
	for(ll i=1;i<=n;i++)b[i]=read();
	for(ll i=1;i<=n;i++)tot+=a[i]*b[i];
	for(ll i=1;i<=n;i++){
		for(ll j=tot;j>=0;j--){
			for(ll k=1;k<=a[i];k++){
				if(j>=k*b[i])f[j]=min(m,max(f[j-k*b[i]]*k,f[j]));
			}
		}
	}
	for(ll i=0;i<=tot;i++){
		if(f[i]==m){
			printf("%lld",i);
			return 0;
		}
	}
	return 0;
}