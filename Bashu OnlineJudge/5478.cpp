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
ll n,m,I,L,R,K,P;
ll gcd(ll x,ll y){
	return y==0?x:gcd(y,x%y);
}
void exgcd(ll a,ll b,ll &x,ll &y){
	if(b==0){x=1;y=0;}
	else{
		exgcd(b,a%b,x,y);
		ll t=x;x=y;y=t-a/b*y;
	}
}
struct Matrix{
	ll a[2][2];
	void Init(){memset(a,0,sizeof(a));}
	friend Matrix operator*(Matrix A,Matrix B){
		Matrix C;C.Init();
		for(ll i=0;i<2;i++){
			for(ll j=0;j<2;j++){
				for(ll k=0;k<2;k++){
					C.a[i][j]+=A.a[i][k]*B.a[k][j];
				}
				C.a[i][j]%=P;
			}
		}
		return C;
	}
};
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	ll T=read();
	while(T--){
		I=read();L=read();R=read();
		K=read();P=read();m=read();
		Matrix A;A.Init();
		A.a[0][0]=1;A.a[0][1]=0;
		A.a[1][0]=0;A.a[1][1]=1;
		Matrix B;B.Init();
		B.a[0][0]=1;B.a[0][1]=1;
		B.a[1][0]=1;B.a[1][1]=0;
		n=K-2;
		while(n){
			if(n&1)A=A*B;
			B=B*B;n>>=1;
		}
		ll a=A.a[0][0];I%=P;
		ll b=(m-I*A.a[0][1]%P+P)%P;
		ll d=gcd(a,P);
		if(b%d){puts("0");continue;}
		ll x=0,y=0,Ans=0;exgcd(a,P,x,y);
		x=(x*(b/d)%(P/d)+(P/d))%(P/d);
		if(R>=x)Ans+=(R-x)/(P/d)+1;
		if(L-1>=x)Ans-=(L-1-x)/(P/d)+1;
		printf("%lld\n",Ans);
	}
	return 0;
}