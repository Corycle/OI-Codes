#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=200005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,ans,top,a[N],g[N],pos[N];
ll gcd(ll x,ll y){
	return y==0?x:gcd(y,x%y);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++)a[i]=read();
	for(ll i=1;i<=n;i++){
		g[++top]=a[i];pos[top]=i;
		for(ll k=top-1;k>=1;k--){
			g[k]=gcd(g[k],g[k+1]);
		}
		ll j=0;
		for(ll k=1;k<=top;){
			g[++j]=g[k];
			pos[j]=pos[k];
			while(g[j]==g[k])k++;
		}
		top=j;
		for(ll k=1;k<=top;k++){
			ans=max(ans,(i-pos[k]+1)*g[k]);
		}
	}
	printf("%lld",ans);
	return 0;
}