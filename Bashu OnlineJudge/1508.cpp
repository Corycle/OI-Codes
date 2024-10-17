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
const int inf=0x3f3f3f3f;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll phi(ll n){
	ll ans=n;
	for(int i=2;i*i<=n;i++){
		if(n%i==0)ans=ans/i*(i-1);
		while(n%i==0)n/=i;
	}
	if(n>1)ans=ans/n*(n-1);
	return ans;
}
ll n;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	while(1){
		n=read();
		if(!n)break;
		printf("%lld\n",phi(n));
	}
	return 0;
}