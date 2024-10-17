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
const ll N=4200005;
const ll M=30;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[M];
ll n,m,F[N],Ans[M];
void FWT(ll a[],ll n,ll f){
	for(ll i=1;i<=(1<<n);i<<=1){
		for(ll j=0;j<=(1<<n);j++){
			if(i&j){
				ll x=a[j-i],y=a[j];
				a[j-i]=x+y;a[j]=x-y;
			}
		}
	}
	if(f==-1)for(ll i=0;i<=(1<<n);i++)a[i]/=(1<<n);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=n;i++){
		ll sta=0;
		scanf("%s",s+1);
		for(ll j=1;j<=m;j++){
			sta=(sta<<2)|(s[j]-'0');
		}
		F[sta]++;
	}
	ll Max=1<<(m*2);
	FWT(F,m*2,1);
	for(ll i=0;i<Max;i++)F[i]=F[i]*F[i];
	FWT(F,m*2,-1);
	for(ll i=0;i<Max;i++){
		ll dis=0,tmp=i;
		for(ll j=1;j<=m;j++){
			ll t=tmp&3;tmp>>=2;
			if(t==0)dis+=0;
			if(t==1)dis+=1;
			if(t==2)dis+=2;
			if(t==3)dis+=1;
		}
		Ans[dis]+=F[i];
	}
	Ans[0]-=n;
	for(ll i=0;i<=2*m;i++)printf("%lld\n",Ans[i]/2);
	return 0;
}