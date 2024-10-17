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
#define ld long double
using namespace std;
const int inf=0x3f3f3f3f;
const ld Pi=acos(-1);
const int MOD=1<<15;
const int Mod=1e9+7;
const int Phi=1e9+6;
const int N=2e5+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m;
int Ans,len,L,R[N];
int a[N],b[N],P[N],fac[N],inv[N];
int mod(int x){return x>=Mod?x-Mod:x;}
struct Complex{
	ld r,i;
	friend Complex operator+(Complex A,Complex B){return (Complex){A.r+B.r,A.i+B.i};}
	friend Complex operator-(Complex A,Complex B){return (Complex){A.r-B.r,A.i-B.i};}
	friend Complex operator*(Complex A,Complex B){return (Complex){A.r*B.r-A.i*B.i,A.r*B.i+A.i*B.r};}
	friend Complex operator*(Complex A,ld B){return (Complex){A.r*B,A.i*B};}
	friend Complex operator/(Complex A,ld B){return (Complex){A.r/B,A.i/B};}
};
Complex a1[N],a2[N],b1[N],b2[N],c1[N],c2[N],c3[N];
int Pow(int x,int y){int ans=1;while(y){if(y&1)ans=1ll*ans*x%Mod;x=1ll*x*x%Mod;y>>=1;}return ans;}
void Prepare(int maxn){
	fac[0]=fac[1]=inv[0]=inv[1]=P[0]=1;
	for(int i=1;i<=maxn;i++)P[i]=mod(P[i-1]<<1);
	for(int i=2;i<=maxn;i++)fac[i]=1ll*fac[i-1]*i%Mod;
	for(int i=2;i<=maxn;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<=maxn;i++)inv[i]=1ll*inv[i-1]*inv[i]%Mod;
}
int C(int n,int m){return n<m?0:1ll*fac[n]*inv[m]%Mod*inv[n-m]%Mod;}
void Init(int maxn){
	len=1;L=0;while(len<=maxn){len<<=1;L++;}
	for(int i=0;i<len;i++)R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
}
void FFT(Complex a[],int n,int f){
	for(int i=0;i<n;i++)if(i<R[i])swap(a[i],a[R[i]]);
	for(int i=1;i<n;i<<=1){
		Complex Wn=(Complex){cos(Pi/i),f*sin(Pi/i)};
		for(int j=0;j<n;j+=(i<<1)){
			Complex W=(Complex){1,0};
			for(int k=0;k<i;k++){
				Complex x=a[j+k],y=a[j+k+i]*W;
				a[j+k]=x+y;a[j+k+i]=x-y;W=W*Wn;
			}
		}
	}
	if(f==-1)for(int i=0;i<n;i++)a[i]=a[i]/n;
}
void Multi(int a[],int b[],int c[]){
	for(int i=0;i<len;i++){
		a1[i]=(Complex){a[i]/MOD,0};a2[i]=(Complex){a[i]%MOD,0};
		b1[i]=(Complex){b[i]/MOD,0};b2[i]=(Complex){b[i]%MOD,0};
	}
	FFT(a1,len,1);FFT(a2,len,1);FFT(b1,len,1);FFT(b2,len,1);
	for(int i=0;i<len;i++){
		c1[i]=a1[i]*b1[i];
		c2[i]=a1[i]*b2[i]+a2[i]*b1[i];
		c3[i]=a2[i]*b2[i];
	}
	FFT(c1,len,-1);FFT(c2,len,-1);FFT(c3,len,-1);
	for(int i=0;i<len;i++){
		c[i]=(ll)(round(c3[i].r))%Mod;
		c[i]=(c[i]+(((ll)(round(c1[i].r))%Mod)<<30))%Mod;
		c[i]=(c[i]+(((ll)(round(c2[i].r))%Mod)<<15))%Mod;
		c[i]=mod(c[i]+Mod);
	}
}
void Solve(ll n){
	if(n==1){for(int i=1;i<=m;i++)a[i]=1;return;}
	if(n&1){
		Solve(n-1);
		for(int i=1;i<=m;i++){
			a[i]=1ll*a[i]*inv[i]%Mod*P[i]%Mod;
			b[i]=inv[i];
		}
		Multi(a,b,a);
		for(int i=0;i<=m;i++)a[i]=1ll*a[i]*fac[i]%Mod;
		for(int i=m+1;i<len;i++)a[i]=0;
		return;
	}
	Solve(n>>1);
	for(int i=1;i<=m;i++){
		int x=a[i];
		a[i]=1ll*x*inv[i]%Mod*Pow(P[i],(n>>1)%Phi)%Mod;
		b[i]=1ll*x*inv[i]%Mod;
	}
	Multi(a,b,a);
	for(int i=0;i<=m;i++)a[i]=1ll*a[i]*fac[i]%Mod;
	for(int i=m+1;i<len;i++)a[i]=0;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	if(n>m){puts("0");return 0;}
	Prepare(m);Init(m+m);Solve(n);
	for(int i=0;i<=m;i++)Ans=mod(Ans+1ll*a[i]*C(m,i)%Mod);
	printf("%d",Ans);
	return 0;
}
