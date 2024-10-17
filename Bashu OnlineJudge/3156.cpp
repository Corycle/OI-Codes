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
ll n,m,a[N],f1[N],f2[N];
struct Node{ll l,r;}P[N];
ll Pow(ll x,ll y){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=ans*tot%Mod;
		tot=tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
ll Sum(ll num){
	return (Pow(2,num)-1+Mod)%Mod;
}
int main(){
//	freopen("mineral.in","r",stdin);
//	freopen("mineral.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=n;i++){
		P[i].l=read();
		P[i].r=read();
	}
	for(ll i=1;i<=m;i++)a[i]=read();
	sort(a+1,a+m+1);ll tot=0;
	for(ll i=1;i<=n;i++){
		ll L=lower_bound(a+1,a+m+1,P[i].l)-a;
		ll R=upper_bound(a+1,a+m+1,P[i].r)-a-1;
		if(L<=R)P[++tot]=(Node){L,R};
	}
	n=tot;
	for(ll i=1;i<=n;i++){
		f1[P[i].l]++;
		f2[P[i].r]++;
	}
	ll Ans=0,num=0;
	for(ll i=1;i<=m;i++){
		num-=f2[i-1];
		Ans=(Ans-Sum(num)+Mod)%Mod;
		num+=f1[i];
		Ans=(Ans+Sum(num))%Mod;
	}
	printf("%lld",Ans);
	return 0;
}