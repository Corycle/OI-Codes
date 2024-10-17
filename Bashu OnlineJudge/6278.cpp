/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
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
const ll Mod=19921107;
const ll N=205;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,cnt,b[N],P[N];
struct Matrix{ll a[N][N];}A,B;
Matrix Multi(Matrix A,Matrix B){
	Matrix C;
	memset(C.a,0,sizeof(C.a));
	for(ll i=1;i<=cnt;i++){
		for(ll j=1;j<=cnt;j++){
			for(ll k=1;k<=cnt;k++){
				C.a[i][j]=(C.a[i][j]+A.a[i][k]*B.a[k][j]%Mod)%Mod;
			}
		}
	}
	return C;
}
void DFS(ll depth,ll sta){
	if(depth>n){
		if(n==1||!((sta&1)&&(sta&P[n-1])))b[++cnt]=sta;
		return;
	}
	DFS(depth+1,sta);
	DFS(depth+2,sta|P[depth-1]);
}
void Solve(ll t){
	while(t){
		if(t&1)B=Multi(B,A);
		A=Multi(A,A);
		t>>=1;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();P[0]=1;
	for(ll i=1;i<=n;i++)P[i]=P[i-1]<<1;
	DFS(1,0);
	if(m==1){printf("%d\n",cnt);return 0;}
	for(ll i=1;i<=cnt;i++){
		for(ll j=1;j<=cnt;j++){
			if(!(b[i]&b[j]))A.a[i][j]=1;
		}
	}
	memcpy(B.a,A.a,sizeof(B.a));
	Solve(m-2);
	ll ans=0;
	for(ll i=1;i<=cnt;i++){
		for(ll j=1;j<=cnt;j++){
			if(!(b[i]&b[j]))ans=(ans+B.a[i][j])%Mod;
		}
	}
	printf("%lld\n",ans);
	return 0;
}