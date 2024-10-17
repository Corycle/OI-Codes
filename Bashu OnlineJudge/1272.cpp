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
const ll Mod=1e9+7;
const ll N=1005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n;
ll a[N][N];
ll Pow(ll x,ll y,ll mod){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=(ans*tot)%mod;
		tot=(tot*tot)%mod;
		y/=2;
	}
	return ans;
}
ll Inv(ll x,ll p){
	return Pow(x,p-2,p);
}
void Deal(ll x){
	int k=x;
	ll Max=a[x][x];
	for(int i=x+1;i<=n;i++){
		if(a[i][x]>Max){
			Max=a[i][x];k=i;
		}
	}
	for(int i=x;i<=n*2;i++){
		swap(a[x][i],a[k][i]);
	}
	if(a[x][x]==0){
		printf("No Solution");
		exit(0);
	}
	ll inv=Inv(a[x][x],Mod);
	for(int i=1;i<=n;i++){
		if(i!=x){
			ll p=a[i][x]*inv%Mod;
			for(ll j=x;j<=2*n;j++){
				a[i][j]=(a[i][j]-p*a[x][j]%Mod+Mod)%Mod;
			}
		}
	}
}
void Gauss(){
	for(int i=1;i<=n;i++){
		Deal(i);
		int inv=Inv(a[i][i],Mod);
		for(int j=1;j<=n*2;j++){
			a[i][j]=a[i][j]*inv%Mod;
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			a[i][j]=read();
		}
		a[i][i+n]=1;
	}
	Gauss();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			printf("%lld ",a[i][j+n]);
		}
		printf("\n");
	}
	return 0;
}