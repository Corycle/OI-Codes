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
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,F0,F1,Mod;
ll mod(ll x){return x>=Mod?x-Mod:x;}
struct Matrix{
	ll a[3][3];
	void Init(){memset(a,0,sizeof(a));}
	friend Matrix operator*(Matrix A,Matrix B){
		Matrix C;C.Init();
		for(ll i=0;i<3;i++){
			for(ll j=0;j<3;j++){
				for(ll k=0;k<3;k++){
					C.a[i][j]=mod(C.a[i][j]+A.a[i][k]*B.a[k][j]%Mod);
				}
			}
		}
		return C;
	}
}Ans,tot;
void Solve(ll t){
	while(t){
		if(t&1)Ans=Ans*tot;
		tot=tot*tot;
		t>>=1;
	}
}
int main(){
//	freopen("fib.in","r",stdin);
//	freopen("fib.out","w",stdout);
	F0=read();F1=read();Mod=read();n=read();
	tot.a[0][0]=1;tot.a[0][1]=1;tot.a[0][2]=2;
	tot.a[1][0]=1;tot.a[1][1]=0;tot.a[1][2]=0;
	tot.a[2][0]=1;tot.a[2][1]=0;tot.a[2][2]=1;
	Ans.a[0][0]=1;Ans.a[1][1]=1;Ans.a[2][2]=1;
	Solve(n-1);
	ll tmp=(ll)(sqrt(3+F0*F1));
	ll Fn=(Ans.a[0][0]*F1+Ans.a[0][1]*F0+Ans.a[0][2]*tmp)%Mod;
	printf("%lld",Fn);
	return 0;
}