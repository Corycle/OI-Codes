#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,k,ans;
ll F(ll x){
	if(x%4==0)return x;
	if(x%4==1)return 1;
	if(x%4==2)return x+1;
	return 0;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();k=sqrt(n);
	for(ll i=1;i<=k;i++){
		ll sum=n/i;
		ll fact=sum-(i-1);
		if(fact&1)ans^=i;
		ans^=F(sum)^F(i-1)^i;
	}
	printf("%lld",ans);
	return 0;
}
