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
const ll inf=0x3f3f3f3f;
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,V1,V2;
ll a[N],c[N],Max[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	m=read();n=read();
	V1=read();V2=read();
	for(ll i=1;i<=n;i++){
		a[i]=read();
		c[i]=read();
		Max[i]=i;
	}
	for(ll i=n-1;i>=0;i--){
		if(c[Max[i]]<c[Max[i+1]])Max[i]=Max[i+1];
	}
	ll A=1,Ans=0,pos=0;
	while(A<=n){
		ll dis=a[Max[A]]-pos;
		Ans+=c[Max[A]]*dis*(V1-V2);
		pos=a[Max[A]];A=Max[A]+1;
	}
	printf("%lld",Ans);
	return 0;
}