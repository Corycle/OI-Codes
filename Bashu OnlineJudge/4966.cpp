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
const ll N=105;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,K,r,Mod;
struct Matrix{ll a[N][N];};
Matrix Multi(Matrix A,Matrix B){
	Matrix C;
	memset(C.a,0,sizeof(C.a));
	for(ll i=1;i<=K;i++){
		for(ll j=1;j<=K;j++){
			for(ll k=1;k<=K;k++){
				C.a[i][j]=(C.a[i][j]+A.a[i][k]*B.a[k][j])%Mod;
			}
		}
	}
	return C;
}
Matrix A;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Mod=read();K=read();r=read();
	for(ll i=1;i<=K;i++){
		A.a[i][i-1]++;
		A.a[i][i]++;
	}
	A.a[1][K]++;
	Matrix B=A;
	ll tot=n*K-1;
	while(tot){
		if(tot&1)A=Multi(A,B);
		B=Multi(B,B);
		tot>>=1;
	}
	printf("%lld",A.a[r+1][1]);
	return 0;
}