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
const ll Mod=998244353;
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,fac[N],inv[N];
ll a[N],b[N],p1[N],p2[N];
struct Tree{
	ll c[N];
	ll lowbit(ll x){return x&(-x);}
	void Add(ll x,ll y){for(;x<=n;x+=lowbit(x))c[x]+=y;}
	ll Ask(ll x){ll ans=0;for(;x>=1;x-=lowbit(x))ans+=c[x];return ans;}
}tree;
void Prepare(){
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(ll i=2;i<=n;i++)fac[i]=fac[i-1]*i%Mod;
	for(ll i=2;i<=n;i++)inv[i]=inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(ll i=2;i<=n;i++)inv[i]=inv[i-1]*inv[i]%Mod;
}
ll C(ll n,ll m){
	return n<m?0:fac[n]*inv[m]%Mod*inv[n-m]%Mod;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Prepare();
	for(ll i=1;i<=n;i++){
		a[i]=b[i]=read();
	}
	sort(b+1,b+n+1);
	for(ll i=1;i<=n;i++){
		p1[i]=n+1-(lower_bound(b+1,b+n+1,a[i])-b);
		p2[i]=n+1-(upper_bound(b+1,b+n+1,a[i]*2)-b-1);
		tree.Add(p2[i],1);tree.Add(p1[i],-1);
//		cout<<p1[i]<<" "<<p2[i]<<endl;
	}
	for(ll i=1;i<=n;i++){
		ll Ans=0;
		if(a[i]==0){printf("%lld\n",C(n,m));continue;}
		ll pos=n+1-(lower_bound(b+1,b+n+1,a[i]*2)-b-1);
		ll num1=tree.Ask(p1[i]),num2=(p1[i]-pos+1);
		if(n-num1-1>=0)Ans=(Ans+C(n-num1-1,m))%Mod;
		if(n-num2>=0&&m-num2>=0)Ans=(Ans+C(n-num2,m-num2))%Mod;
//		cout<<num1<<" "<<num2<<" "<<pos<<endl;
		printf("%lld\n",Ans);
	}
	return 0;
}