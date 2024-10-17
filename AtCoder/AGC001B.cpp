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
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,a,b,Ans;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();a=read();b=n-a;Ans=n;
	while(1){
		if(!a||!b)break;
		if(a==b){Ans+=a;break;}
		if(a<b)swap(a,b);
		ll num=(a-b)/b;
		if(num){Ans+=b*num*2;a-=b*num;}
		else{Ans+=b*2;a-=b;}
	}
	printf("%lld\n",Ans);
	return 0;
}
