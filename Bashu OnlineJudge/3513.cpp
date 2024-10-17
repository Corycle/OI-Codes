#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
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
const ll N=5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll mod;
struct Matrix{
	ll n,m,a[N][N];
	void Clean(){
		n=m=0;
		memset(a,0,sizeof(a));
	}
};
Matrix Multi(Matrix A,Matrix B){
	Matrix C;C.Clean();
	C.n=A.n;C.m=B.m;
	for(ll i=1;i<=C.n;i++){
		for(ll j=1;j<=C.m;j++){
			for(ll k=1;k<=A.m;k++){
				C.a[i][j]=(C.a[i][j]+A.a[i][k]*B.a[k][j]%mod)%mod;
			}
		}
	}
	return C;
}
Matrix Pow(Matrix A,Matrix B,ll y){
	Matrix ans=A,tot=B;
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
	ll p=read(),q=read();
	ll a1=read(),a2=read();
	ll n=read();mod=read();
	if(n==1){printf("%lld",a1%mod);return 0;}
	if(n==2){printf("%lld",a2%mod);return 0;}
	Matrix A,B;
	A.Clean();B.Clean();
	A.n=1;A.m=2;B.n=2;B.m=2;
	A.a[1][1]=a1;A.a[1][2]=a2;
	B.a[1][1]=0;B.a[1][2]=q;
	B.a[2][1]=1;B.a[2][2]=p;
	Matrix ans=Pow(A,B,n-2);
	printf("%lld",ans.a[1][2]);
	return 0;
}