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
const int N=105;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,dlt;
ll p[N],d[N];
void Insert(ll x){
	for(ll i=50;i>=0;i--){
		if((x>>i)&1){
			if(!p[i]){p[i]=x;break;}
			x^=p[i];
		}
	}
}
ll Ask(){
	ll ans=0;
	for(int i=50;i>=0;i--){
		if(ans<(ans^p[i]))ans^=p[i];
		if(p[i])dlt=p[i];
	}
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		ll x=read();
		Insert(x);
	}
	ll ans1=Ask();
	ll ans2=ans1^dlt;
	printf("%lld %lld",ans1,ans2);
	return 0;
}