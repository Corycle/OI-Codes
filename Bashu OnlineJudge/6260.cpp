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
const ll N=300005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,a[N],f[N],vis[N];
int main(){
//	freopen("tree.in","r",stdin);
//	freopen("tree.out","w",stdout);
	n=read();
	ll S=(1<<18)-1,T=S;
	for(ll i=1;i<=n;i++){
		a[i]=read();
		S&=a[i];
	}
	for(ll i=1;i<=n;i++)a[i]^=S;
	for(ll i=1;i<=n;i++)vis[a[i]^T]=1;//~a[i]
	for(ll i=T;i>=1;i--){
		for(ll j=0;j<=17;j++){
			vis[i]|=vis[i|(1<<j)];
		}
	}
	memset(f,0x3f,sizeof(f));
	for(ll i=1;i<=n;i++)f[a[i]]=a[i];
	for(ll i=T;i>=1;i--){
		if(f[i]>=f[0])continue;
		for(ll j=i;j;j=(j-1)&i){
			if(vis[j])f[i^j]=min(f[i^j],f[i]+(i^j));
		}
	}
	printf("%lld",S*n+f[0]);
	return 0;
}
/*
5
9 12 14 15 17
*/