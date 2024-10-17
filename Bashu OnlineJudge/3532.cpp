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
/*
	ax≡1(mod b) 
	ax+by=1
	
*/
void Exgcd(ll a,ll b,ll &d,ll &x,ll &y){
	if(!b){
		d=a;x=1;y=0;
	}
	else{
		Exgcd(b,a%b,d,x,y);
		ll t=x;x=y;y=t-a/b*y;
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	ll a=read(),b=read(),x,y,d;
	Exgcd(a,b,d,x,y);
	ll ans=((x%(b/d)+b/d)%(b/d));
	printf("%lld",ans);
	return 0;
}