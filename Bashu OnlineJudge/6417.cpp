/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<cstring>
#include<complex>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,k,f;
int main(){
//	freopen("code.in","r",stdin);
//	freopen("code.out","w",stdout);
	n=read();k=read();
	for(ll i=n-1;i>=0;i--){
		ll c=((k>>i)&1)^f;
		if(c){
			printf("1");
			f^=1;
		}
		else{
			printf("0");
		}
	}
	return 0;
}