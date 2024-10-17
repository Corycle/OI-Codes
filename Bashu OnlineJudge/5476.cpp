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
const ll Mod=1e9+7;
const ll N=105;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,K,fa[N],a[N][N],c[N][N];
ll Pow(ll x,ll y){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=ans*tot%Mod;
		tot=tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
void Add(ll val){
	for(ll i=0;i<n;i++){
		c[i][i]=n-1;
		for(ll j=i+1;j<n;j++){
			c[i][j]=c[j][i]=-1;
		}
	}
	for(ll i=1;i<n;i++){
		ll x=fa[i],y=i;
		c[x][x]=c[x][x]+val-1;
		c[y][y]=c[y][y]+val-1;
		c[x][y]=c[x][y]+1-val;
		c[y][x]=c[y][x]+1-val;
	}
}
ll Kirchhoff(ll n){//求行列式 
	ll ans=1;
	for(ll i=0;i<=n;i++){
		for(ll k=i+1;k<=n;k++){
			while(c[k][i]){
				ll d=c[i][i]/c[k][i];
				for(ll j=i;j<=n;j++){
					c[i][j]=(c[i][j]-d*c[k][j]%Mod+Mod)%Mod;
				}
				swap(c[i],c[k]);
				ans=-ans;
			}
		}
		ans=ans*c[i][i]%Mod;
	}
	return (ans+Mod)%Mod;
}
void Gauss(){//高斯消元，求解析式 
	for(ll i=0;i<n;i++){
		for(ll k=i+1;k<n;k++){
			while(a[k][i]){
				ll d=a[i][i]/a[k][i];
				for(ll j=i;j<=n;j++){
					a[i][j]=(a[i][j]-d*a[k][j]%Mod+Mod)%Mod;
				}
				swap(a[i],a[k]);
			}
		}
	}
	for(ll i=n-1;i>=0;i--){
		a[i][i]=a[i][n]*Pow(a[i][i],Mod-2)%Mod;
		for(ll j=i-1;j>=0;j--){
			a[j][n]=(a[j][n]-a[i][i]*a[j][i]%Mod+Mod)%Mod;
		}
	}
}
int main(){
//	freopen("tree.in","r",stdin);
//	freopen("tree.out","w",stdout);
	n=read();K=read();
	for(ll i=1;i<n;i++)fa[i]=read();
	for(ll i=1;i<=n;i++){
		Add(i);
		a[i-1][0]=1;
		for(ll j=1;j<n;j++)a[i-1][j]=a[i-1][j-1]*i%Mod;
		a[i-1][n]=Kirchhoff(n-2);
	}
	Gauss();
	ll ans=0;
	for(ll i=n-K-1;i<n;i++){
		ans=(ans+a[i][i])%Mod;
	}
	printf("%lld",ans);
	return 0;
}