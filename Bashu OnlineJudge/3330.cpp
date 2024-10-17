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
const ll Inv2=5e8+5;
const ll Mod=1e9+9;
const ll N=2e6+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,p,top;
ll a[N],L[N],R[N],U[N],D[N];
struct BIT{
	ll n,c[N];
	ll lowbit(ll x){return x&(-x);}
	void Add(ll x,ll y){
		for(ll i=x;i<=n;i+=lowbit(i))c[i]+=y;
	}
	ll Ask(ll x){
		ll ans=0;
		for(ll i=x;i>=1;i-=lowbit(i))ans+=c[i];
		return ans;
	}
}A,B,C;
inline ll ID(ll x,ll y){
	if(x<1||y<1||x>n||y>m)return 0;
	return (x-1)*m+y;
}
void Clear(ll maxn){
	A.n=B.n=C.n=maxn;
	for(ll i=0;i<=maxn;i++){
		A.c[i]=B.c[i]=C.c[i]=0;
	}
}
void Update(ll x,ll y){
	ll t=L[ID(x,y)];
	A.Add(t,(x-top));
	B.Add(t,(x-top)*t%Mod);
	C.Add(t,(x-top)*t%Mod*t%Mod);
}
ll Sum(ll x,ll y,ll maxn){
	ll t=L[ID(x,y)];
	ll s1=(A.Ask(maxn)-A.Ask(t)+Mod)%Mod;
	ll s2=B.Ask(t),s3=C.Ask(t),ans=0;
	ans=(t*s2%Mod-(s3+s2)%Mod*Inv2%Mod+Mod)%Mod;
	ans=(ans+t*(t-1)%Mod*Inv2%Mod*s1%Mod)%Mod;
	return ans*D[ID(x,y)]%Mod;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();p=read();
	memset(a,-1,sizeof(a));
	for(ll i=1;i<=p;i++){
		ll x=read(),y=read();
		a[ID(x,y)]=0;
	}
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=m;j++){
			a[ID(i,j)]=-a[ID(i,j)];
		}
	}
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=m;j++)L[ID(i,j)]=a[ID(i,j)]?L[ID(i,j-1)]+1:0;
		for(ll j=m;j>=1;j--)R[ID(i,j)]=a[ID(i,j)]?R[ID(i,j+1)]+1:0;
		for(ll j=1;j<=m;j++)L[ID(i,j)]=min(L[ID(i,j)],R[ID(i,j)]);
	}
	for(ll j=1;j<=m;j++){
		for(ll i=1;i<=n;i++)U[ID(i,j)]=a[ID(i,j)]?U[ID(i-1,j)]+1:0;
		for(ll i=n;i>=1;i--)D[ID(i,j)]=a[ID(i,j)]?D[ID(i+1,j)]+1:0;
	}
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=m;j++){
			ll t=ID(i,j);
			if(L[t])L[t]--;if(R[t])R[t]--;
			if(U[t])U[t]--;if(D[t])D[t]--;
		}
	}
	ll ans=0;
	for(ll j=1;j<=m;j++){
		ll maxn=min(j-1,m-j);
		top=0;Clear(maxn);
		for(ll i=1;i<=n;i++){
			if(!top&&a[ID(i,j)])top=i;
			if(top&&!a[ID(i,j)]){
				Clear(maxn);top=0;
				continue;
			}
			if(!top||i==top)continue;
			if(top<=i-3&&L[ID(i,j)]>1)ans=(ans+Sum(i,j,maxn))%Mod;
			if(top!=i-1&&L[ID(i-1,j)])Update(i-1,j);
		}
	}
	printf("%lld",ans);
	return 0;
}