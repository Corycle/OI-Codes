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
const int inf=0x3f3f3f3f;
const int Mod=65537;
const int Phi=65536;
const int N=100005;
const int G=3;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m;
int mod(int x){return x>=Mod?x-Mod:x;}
int Pow(ll x,ll y){
	int ans=1,tot=x%Mod;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
namespace Task1{
	int len,L,R[N];
	void NTT(int a[],int n,int f){
		for(int i=0;i<n;i++)if(i<R[i])swap(a[i],a[R[i]]);
		for(int i=1;i<n;i<<=1){
			int Wn=Pow(G,Phi+f*Phi/(i<<1));
			for(int j=0;j<n;j+=(i<<1)){
				int W=1;
				for(int k=0;k<i;k++){
					int x=a[j+k],y=1ll*W*a[j+k+i]%Mod;
					a[j+k+i]=mod(x-y+Mod);
					a[j+k]=mod(x+y);
					W=1ll*W*Wn%Mod;
				}
			}
		}
		if(f==-1){
			int Inv=Pow(n,Mod-2);
			for(int i=0;i<n;i++)a[i]=1ll*a[i]*Inv%Mod;
		}
	}
	int a[N],b[N];
	void Multi(int A[],int B[],int C[]){
		L=0;len=1;while(len<=m+m){len<<=1;L++;}
		for(int i=0;i<len;i++)R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
		for(int i=0;i<len;i++){a[i]=A[i];b[i]=B[i];}
		NTT(a,len,1);NTT(b,len,1);
		for(int i=0;i<len;i++)a[i]=1ll*a[i]*b[i]%Mod;
		NTT(a,len,-1);
		for(int i=m*2;i>m;i--){
			a[i-1]=mod(a[i-1]+mod(a[i]+a[i]));
			a[i-m-1]=mod(a[i-m-1]-a[i]+Mod);
		}
		for(int i=0;i<=m;i++)C[i]=a[i];
	}
	int A[N],B[N],F[N];
	void Solve(ll t){
		for(int i=0;i<=m;i++)A[i]=B[i]=0;
		A[0]=1;B[1]=1;
		while(t){
			if(t&1)Multi(A,B,A);
			Multi(B,B,B);
			t>>=1;
		}
	}
	int Ask(ll n){
		int ans=0;Solve(n);
		for(int i=0;i<=m;i++)ans=mod(ans+1ll*F[i]*A[i]%Mod);
		return ans;
	}
	void Main(){
		F[0]=1;
		for(int i=1;i<=m;i++)F[i]=mod(F[i-1]<<1);
		printf("%d",mod(Ask(n+1)-Ask(n)+Mod));
	}
}
namespace Task2{
	int fac[N],inv[N];
	void Prepare(){
		fac[0]=fac[1]=inv[0]=inv[1]=1;
		for(int i=2;i<Mod;i++)fac[i]=1ll*fac[i-1]*i%Mod;
		for(int i=2;i<Mod;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
		for(int i=2;i<Mod;i++)inv[i]=1ll*inv[i-1]*inv[i]%Mod;
	}
	int C(int n,int m){return n<m?0:1ll*fac[n]*inv[m]%Mod*inv[n-m]%Mod;}
	int Lucas(ll n,ll m){
		if(n<m)return 0;
		int ans=1;
		while(m){
			ans=1ll*ans*C(n%Mod,m%Mod)%Mod;
			n/=Mod;m/=Mod;
		}
		return ans;
	}
	int Ask(ll n){
		int ans=0;
		for(int i=0;i<=n/(m+1);i++){
			ans=mod(ans+1ll*Pow(Mod-1,i)*Pow(2,n-i*(m+1))%Mod*Lucas(n-i*m,i)%Mod);
		}
		return ans;
	}
	void Main(){
		Prepare();
		printf("%d",mod(Ask(n+1)-Ask(n)+Mod));
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	if(m<=30000)Task1::Main();
	else Task2::Main();
	return 0;
}