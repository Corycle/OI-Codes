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
const ll N=1005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,l,r,Sta;
ll a[N],s[N],fa[N],mark[N];
ll Find(ll x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
bool Check(ll x,ll y){
	for(ll i=1;i<=n;i++){
		if(((a[i]>>(x-1))^(a[i]>>(y-1)))&1)return false;
	}
	return Find(x)!=Find(y);
}
ll Ask(ll x){
	if(x>Sta)return (1ll<<s[m]);
	ll ans=0;
	memset(mark,-1,sizeof(mark));
	for(ll i=m;i>=1;i--){
		if((x>>(i-1))&1){
			if(mark[Find(i)]!=1)ans+=(1ll<<s[i-1]);
			if(Find(i)==i)mark[i]=1;
			if(mark[Find(i)]==0)break;
		}
		else{
			if(Find(i)==i)mark[i]=0;
			if(mark[Find(i)]==1)break;
		}
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();l=read();r=read();
	for(ll i=1;i<=n;i++)a[i]=read();
	for(ll i=1;i<=m;i++)fa[i]=i;
	for(ll i=1;i<=m;i++){
		for(ll j=i+1;j<=m;j++){
			if(Check(i,j))fa[Find(i)]=Find(j);
		}
	}
	for(ll i=1;i<=m;i++){
		s[i]=s[i-1]+(Find(i)==i);
	}
	Sta=(1ll<<m)-1;
	printf("%lld",Ask(r+1)-Ask(l));
	return 0;
}