/*====Corycle====*/
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
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
const int inf=0x3f3f3f3f;
const int N=1e6+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
bool vis[N];
ll n,g[N],w[N];
int m,cnt,tot,id1[N],id2[N],prime[N];
inline int ID(ll x){return x<=m?id1[x]:id2[n/x];}
inline void Prepare(){
	for(int i=2;i<N;i++){
		if(!vis[i])prime[++cnt]=i;
		for(int j=1;j<=cnt&&1ll*i*prime[j]<N;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
}
ll S(ll n,int x){
	if(n<=1||n<prime[x])return 0;
	ll ans=0;
	for(int i=x+1;i<=cnt&&1ll*prime[i]*prime[i]<=n;i++){
		for(ll Pe=prime[i];Pe<=n/prime[i];Pe=Pe*prime[i]){
			ans+=S(n/Pe,i)+prime[i]*(g[ID(n/Pe)]-(i-1));
		}
	}
	return ans;
}
ll Solve(ll x){
	n=x;m=sqrt(n);tot=0;
	for(ll i=1,j=0;i<=n;i=j+1){
		j=n/(n/i);w[++tot]=n/i;g[tot]=w[tot]-1;
		w[tot]<=m?id1[w[tot]]=tot:id2[n/w[tot]]=tot;
	}
	for(int i=1;i<=cnt;i++){
		for(int j=1;j<=tot&&1ll*prime[i]*prime[i]<=w[j];j++){
			g[j]=g[j]-(g[ID(w[j]/prime[i])]-(i-1));
		}
	}
	return S(n,0);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	ll L=read(),R=read();Prepare();
	printf("%lld",Solve(R)-Solve(L-1));
	return 0;
}