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
const int inf=0x3f3f3f3f;
const ll N=305;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,a[N],sum,tot,ans;
int main(){
	n=read();
	for(ll i=1;i<=n;i++)a[i]=read();
	for(ll i=3;i<=n;i++)sum^=a[i];
	tot=a[1]+a[2];tot-=sum;
	if(tot<0){puts("-1");return 0;}
	for(ll i=42;i>=0;i--){
		if(2*(1ll<<i)<=tot){
			if((sum>>i&1)){puts("-1");return 0;}
			ans+=(1ll<<i);
			tot-=2*(1ll<<i);
		}
	}
	if(tot){puts("-1");return 0;}
	if(ans>a[1]){puts("-1");return 0;}
	for(ll i=42;i>=0;i--){
		if((sum>>i&1)&&(ans+(1ll<<i))<=a[1])ans+=(1ll<<i);
	}
	if(ans==0){puts("-1");return 0;}
	cout<<a[1]-ans;
	return 0;
}
