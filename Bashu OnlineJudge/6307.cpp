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
const ll Mod=1e9+7;
const ll N=1000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
ll n,m,sum,Ans;
ll Pow(ll x,ll y){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=ans*tot%Mod;
		tot=tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
int main(){
//	freopen("elect.in","r",stdin);
//	freopen("elect.out","w",stdout);
	n=read();m=read();
	scanf("%s",s+1);
	for(ll i=n;i>=1;i--){
		if(s[i]=='B'&&sum+1>m){
			Ans=(Ans+Pow(2,i))%Mod;
			s[i]='A';
		}
		if(s[i]=='A')sum--;
		if(s[i]=='B')sum++;
		sum=max(sum,0ll);
	}
	printf("%lld",Ans);
	return 0;
}
