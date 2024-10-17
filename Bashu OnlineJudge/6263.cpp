/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll Mod=998244353;
const ll N=1000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,type,a[N];
struct Matrix{
	ll a[2][2];
	void Init(){
		memset(a,0,sizeof(a));
	}
}Mat[N],Inv[N],PreMat[N],PreInv[N];
Matrix Multi(Matrix A,Matrix B){
	Matrix C;C.Init();
	for(ll i=0;i<2;i++){
		for(ll j=0;j<2;j++){
			for(ll k=0;k<2;k++){
				C.a[i][j]=(C.a[i][j]+A.a[i][k]*B.a[k][j]%Mod)%Mod;
			}
		}
	}
	return C;
}
void Prepare(ll pos,ll x){
	Mat[pos].a[0][0]=x;Mat[pos].a[0][1]=1;
	Mat[pos].a[1][0]=1;Mat[pos].a[1][1]=0;
	Inv[pos].a[0][0]=0;Inv[pos].a[0][1]=1;
	Inv[pos].a[1][0]=1;Inv[pos].a[1][1]=Mod-x;
	PreMat[pos]=Multi(Mat[pos],PreMat[pos-1]);
	PreInv[pos]=Multi(PreInv[pos-1],Inv[pos]);
}
int main(){
//	freopen("horse.in","r",stdin);
//	freopen("horse.out","w",stdout);
	ll Ansx=0,Ansy=0;
	PreMat[0].a[0][0]=1;
	PreMat[0].a[1][1]=1;
	PreInv[0].a[0][0]=1;
	PreInv[0].a[1][1]=1;
	n=read();m=read();type=read();
	for(ll i=1;i<=n;i++){
		a[i]=read();
		Prepare(i,a[i]);
	}
	for(ll i=1;i<=m;i++){
		ll op=read();
		if(op==1){
			ll x=read()^((Ansx^Ansy)*type);
			a[++n]=x;Prepare(n,a[n]);
		}
		if(op==2){
			ll x=read()^((Ansx^Ansy)*type);
			ll y=read()^((Ansx^Ansy)*type);
			Matrix Ans=Multi(PreMat[y],PreInv[x-1]);
			Ansx=Ans.a[0][0];Ansy=Ans.a[0][1];
			printf("%lld %lld\n",Ansx,Ansy);
		}
	}
	return 0;
}