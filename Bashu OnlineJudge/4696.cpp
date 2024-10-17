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
const ll inf=0x3f3f3f3f;
const ll p=1000000007;
const ll N=1005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,k;
ll u[N],r[N],g[N],C[N][N],f[N][N];
ll Pow(ll x,ll y,ll mod){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=(ans*tot)%mod;
		tot=(tot*tot)%mod;
		y>>=1;
	}
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();k=read();
	for(ll i=1;i<=m;i++)u[i]=read();
	for(ll i=1;i<=m;i++)r[i]=read();
	C[0][0]=1;
	for(ll i=1;i<=n+1;i++){
		C[i][0]=1;
		for(ll j=1;j<=i;j++){
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%p;
		}
	}
	f[0][n-1]=1;
	for(ll i=1;i<=m;i++){
		g[0]=u[i];
		for(ll j=1;j<=n;j++){
			g[j]=(Pow(u[i]+1,j+1,p)-1+p)%p;
			for(ll l=0;l<j;l++){
				g[j]=(g[j]-C[j+1][l]*g[l]%p+p)%p;
			}
			g[j]=g[j]*Pow(j+1,p-2,p)%p;
		}
		ll tmp=0;
		ll inv=Pow(u[i],p-2,p);
		ll sum=Pow(u[i],r[i]-1,p);
		for(ll j=0;j<r[i];j++){
			ll dlt=C[r[i]-1][j]*sum%p*g[n-r[i]+j]%p;
			tmp=(tmp+((j&1)?-dlt:dlt)+p)%p;
			sum=sum*inv%p;
		}
		for(ll j=k;j<=n;j++){
			for(ll l=j;l<=n;l++){
				if(n-r[i]-j>=0){
					f[i][j]=(f[i][j]+f[i-1][l]*C[l][j]%p*C[n-l-1][n-r[i]-j]%p*tmp%p)%p;
				}
			}
		}
	}
	printf("%lld",(f[m][k]+p)%p);
	return 0;
}