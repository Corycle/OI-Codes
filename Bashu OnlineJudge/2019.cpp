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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Sum(ll x){
	return (1+x)*x/2;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	ll n=read(),k=read();
	ll ans=n*k,lst=0;
	for(ll i=1;i<=min(n,k);i=lst+1){
		lst=min(n,k/(k/i));
		ans-=(k/i)*(Sum(lst)-Sum(i-1));
	}
	printf("%lld",ans);
	return 0;
}