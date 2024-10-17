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
ll n,m,flag,tot;
ll p[N],d[N];
void Insert(ll x){
	for(ll i=50;i>=0;i--){
		if((x>>i)&1){
			if(!p[i]){p[i]=x;break;}
			x^=p[i];
		}
	}
	if(!x)flag=1;
}
void Build(){
	for(ll i=50;i>=0;i--){
		for(ll j=i-1;j>=0;j--){
			if((p[i]>>j)&1)p[i]^=p[j];
		}
	}
	for(ll i=0;i<=50;i++){
		if(p[i])d[tot++]=p[i];
	}
}
ll Ask(ll k){
	ll ans=0;
	if(flag){
		k--;
		if(!k)return 0;
	}
	if(k>=(1ll<<tot))return -1;
	for(int i=tot;i>=0;i--){
		if((k>>i)&1)ans^=d[i];
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
	Build();
	m=read();
	while(m--){
		ll k=read();
		printf("%lld\n",Ask(k));
	}
	return 0;
}