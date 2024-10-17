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
const ll Mod=998244353;
const ll N=5000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll tot,q[N];

ll gcd(ll x,ll y){
	return y==0?x:gcd(y,x%y);
}
ll Multi(ll x,ll y,ll mod){
	ll ans=0,tot=x;
	while(y){
		if(y&1)ans=(ans+tot)%mod;
		tot=(tot+tot)%mod;
		y/=2;
	}
	return ans;
}
ll Pow(ll x,ll y,ll mod){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=Multi(ans,tot,mod);
		tot=Multi(tot,tot,mod);
		y/=2;
	}
	return ans;
}
bool Miller_Rabin(ll n){
	if(n==2)return true;
	if(n<2||!(n&1))return false;
	ll m=n-1,k=0,cnt=5;
	while(!(m&1)){k++;m>>=1;}
	for(ll i=1;i<=cnt;i++){
		ll a=rand()%(n-1)+1;
		ll x=Pow(a,m,n),y=0;
		for(ll j=1;j<=k;j++){
			y=Multi(x,x,n);
			if(y==1&&x!=1&&x!=n-1)return false;
			x=y;
		}
		if(y!=1)return false;
	}
	return true;
}
ll Pollard_rho(ll n,ll c){
	ll x=rand()%(n-1)+1;
	ll y=x,i=1,k=2;
	while(1){
		i++;
		x=(Multi(x,x,n)+c)%n;
		ll d=gcd((y-x+n)%n,n);
		if(1<d&&d<n)return d;
		if(x==y)return n;
		if(i==k){y=x;k<<=1;}
	}
}
void Find(ll n,ll k){
	if(n==1)return;
	if(Miller_Rabin(n)){
		q[++tot]=n;
		return;
	}
	ll p=n;
	while(p>=n)p=Pollard_rho(p,k--);
	Find(p,k);Find(n/p,k);
}

ll n,K;
struct Matrix{
	ll n,m,a[2][2];
	void Init(){
		n=m=0;
		memset(a,0,sizeof(a));
	}
};
Matrix Matrix_Multi(Matrix A,Matrix B){
	Matrix C;C.Init();
	C.n=A.n;C.m=B.m;
	for(ll k=0;k<A.m;k++){
		for(ll i=0;i<C.n;i++){
			for(ll j=0;j<C.m;j++){
				C.a[i][j]=(C.a[i][j]+(A.a[i][k]*B.a[k][j])%Mod)%Mod;
			}
		}
	}
	return C;
}
Matrix Matrix_Pow(Matrix x,ll y){
	Matrix ans,tot=x;
	ans.Init();ans.n=1;ans.m=2;
	ans.a[0][1]=(K%Mod*((K-1)%Mod)%Mod)%Mod;
	while(y){
		if(y&1)ans=Matrix_Multi(ans,tot);
		tot=Matrix_Multi(tot,tot);
		y>>=1;
	}
	return ans;
}

ll Ans;
Matrix A;
ll Phi(ll x){
	ll ans=x;
	for(ll i=1;i<=tot;i++){
		if(x%q[i]==0){
			ans/=q[i];
			ans*=(q[i]-1);
		}
	}
	return ans%Mod;
}
ll Solve(ll x){
	if(x==1)return 0;
	if(x==2)return K%Mod*((K-1)%Mod)%Mod;
	Matrix ans=Matrix_Pow(A,x-2);
	return ans.a[0][1]%Mod;
}
void DFS(ll depth,ll sum,ll s){
	if(depth==tot+1){
		Ans=(Ans+(Solve(sum)%Mod*Phi(s)%Mod)%Mod)%Mod;
		return;
	}
	ll S=s,Sum=sum;
	DFS(depth+1,Sum,S);
	while(1){
		if(S%q[depth]==0){
			Sum=Sum*q[depth];
			S=S/q[depth];
			DFS(depth+1,Sum,S);
		}
		else break;
	}
}

int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	srand(time(NULL));
	ll T=read();
	while(T--){
		tot=Ans=0;
		n=read();K=read();
		if(n==1){
			printf("%lld\n",K);
			continue;
		}
		Find(n,1000007);
		sort(q+1,q+tot+1);
		tot=unique(q+1,q+tot+1)-q-1;
		A.n=A.m=2;
		A.a[0][0]=0;A.a[0][1]=(K-1)%Mod;
		A.a[1][0]=1;A.a[1][1]=(K-2)%Mod;
		DFS(1,1,n);Ans=(Ans%Mod+Mod)%Mod;
		printf("%lld\n",Ans*Pow(n%Mod,Mod-2,Mod)%Mod);
	}
	return 0;
}