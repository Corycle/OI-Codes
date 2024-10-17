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
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,mod;
struct Matrix{
	ll n,m,a[3][3];
	void Init(ll x,ll y){
		n=x;m=y;
		memset(a,0,sizeof(a));
	}
};
void Prepare(Matrix &p){
	p.Init(2,2);
	p.a[0][0]=1;
	p.a[1][1]=1;
	p.a[2][2]=1;
}
Matrix Multi(Matrix x,Matrix y){
	Matrix z;z.Init(x.n,y.m);
	for(ll k=0;k<=x.m;k++){
		for(ll i=0;i<=z.n;i++){
			for(ll j=0;j<=z.m;j++){
				z.a[i][j]=(z.a[i][j]+x.a[i][k]*y.a[k][j]%mod)%mod;
			}
		}
	}
	return z;
}
ll Pow(ll x,ll y){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=ans*tot%mod;
		tot=tot*tot%mod;
		y>>=1;
	}
	return ans;
}
Matrix Matrix_Pow(Matrix x,ll y){
	Matrix ans,tot=x;Prepare(ans);
	while(y){
		if(y&1)ans=Multi(ans,tot);
		tot=Multi(tot,tot);
		y>>=1;
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();mod=read();
	Matrix ans;
	ll tot=10;
	ans.Init(0,2);
	ans.a[0][2]=1;
	while(tot<=n){
		Matrix x;x.Init(2,2);
		x.a[0][0]=Pow(10,log10(tot));
		x.a[1][0]=x.a[1][1]=1;
		x.a[2][0]=x.a[2][1]=x.a[2][2]=1;
		x=Matrix_Pow(x,tot-(tot/10));
		ans=Multi(ans,x);
		tot*=10;
	}
	Matrix x;x.Init(2,2);
	x.a[0][0]=Pow(10,log10(tot));
	x.a[1][0]=x.a[1][1]=1;
	x.a[2][0]=x.a[2][1]=x.a[2][2]=1;
	x=Matrix_Pow(x,n-(tot/10)+1);
	ans=Multi(ans,x);
	printf("%lld",ans.a[0][0]);
	return 0;
}