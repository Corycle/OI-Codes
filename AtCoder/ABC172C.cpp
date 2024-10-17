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
#define pii pair<ll,ll>
#define fst first
#define scd second
#define mp make_pair
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=2e5+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,k,ans,a[N],b[N];
int main(){
	n=read(),m=read(),k=read();
	for(ll i=1;i<=n;i++)a[i]=read()+a[i-1];
	for(ll i=1;i<=m;i++)b[i]=read()+b[i-1];
	for(ll i=0;i<=n;i++){
		if(k>=a[i]){
			ll j=upper_bound(b+1,b+m+1,k-a[i])-b;
			ans=max(ans,i+j-1);
		}
	}
	cout<<ans<<endl;
	return 0;
}
