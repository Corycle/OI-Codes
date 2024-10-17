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
const ll inf=0x7f7f7f7f7f7f7f7f;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n;
int main(){
//	freopen("wall.in","r",stdin);
//	freopen("wall.out","w",stdout);
	n=read();
	ll tot=1,k=1;
	for(ll i=1;;i++){
		tot+=i*6;
		if(tot>n){
			tot-=i*6;
			break;
		}
		k++;
	}
	if(n==tot)printf("%lld",6*k);
	else printf("%lld",k*6+(n-tot)/k+1);
	return 0;
}