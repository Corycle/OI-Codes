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
const ll N=200005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,tot,Ans;
ll a[N],s1[N],s2[N],pos[N];
int main(){
//	freopen("jerry.in","r",stdin);
//	freopen("jerry.out","w",stdout);
	ll T=read();
	while(T--){
		n=read();Ans=-inf;tot=0;
		for(ll i=1;i<=n;i++)a[i]=read();
		for(ll i=1;i<=n;i++)s1[i]=s1[i-1]+a[i];
		for(ll i=1;i<=n;i++)s2[i]=s2[i-1]+abs(a[i]);
		for(ll i=1;i<=n;i++)if(a[i]<0)pos[++tot]=i;
		for(ll i=1;i<tot;i++){
			Ans=max(Ans,(s1[pos[i]-1])-(s2[pos[i+1]-1]-s2[pos[i]-1])+(s2[n]-s2[pos[i+1]-1]));
		}
		printf("%lld\n",max(Ans,s1[n]));
	}
	return 0;
}