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
const int N=524300;
const int M=32767;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,Mod,ans;
int cnt,mu[N],vis[N],prime[N];
int len,L,R[N],F[N],G[N],inv[N];
int t1[N],t2[N],t3[N],t4[N],t5[N];
int mod(int x){return x>=Mod?x-Mod:x;}
struct Complex{
	ld r,i;
	Complex conj(){return (Complex){r,-i};}
	friend Complex operator+(Complex A,Complex B){return (Complex){A.r+B.r,A.i+B.i};}
	friend Complex operator-(Complex A,Complex B){return (Complex){A.r-B.r,A.i-B.i};}
	friend Complex operator*(Complex A,Complex B){return (Complex){A.r*B.r-A.i*B.i,A.r*B.i+A.i*B.r};}
}a[N],b[N],A1[N],A2[N],B1[N],B2[N];
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
void GetMu(int maxn){
	inv[1]=mu[1]=1;
	for(int i=2;i<=maxn;i++){
		inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
		if(!vis[i]){prime[++cnt]=i;mu[i]=-1;}
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j])mu[i*prime[j]]=-mu[i];
			else{mu[i*prime[j]]=0;break;}
		}
	}
}
void Prepare(int n){
	len=1;L=0;while(len<n){len<<=1;L++;}
	for(int i=0;i<len;i++)R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
}
void FFT(Complex a[],int n){
	for(int i=0;i<n;i++)if(i<R[i])swap(a[i],a[R[i]]);
	for(int i=1;i<n;i<<=1){
		Complex Wn=(Complex){cos(Pi/i),sin(Pi/i)};
		for(int j=0;j<n;j+=(i<<1)){
			Complex W=(Complex){1,0};
			for(int k=0;k<i;k++){
				Complex x=a[j+k],y=W*a[j+k+i];
				a[j+k]=x+y;a[j+k+i]=x-y;W=W*Wn;
			}
		}
	}
}
void MTT(int A[],int B[],int C[],int n){
	Prepare(n+n);
	for(int i=0;i<n;++i){
		a[i]=(Complex){(ld)(A[i]&M),(ld)(A[i]>>15)};
		b[i]=(Complex){(ld)(B[i]&M),(ld)(B[i]>>15)};
		a[i+n]=b[i+n]=(Complex){0,0};
	}
	FFT(a,len),FFT(b,len);
	for(int i=0;i<len;++i){
		int j=(len-i)&(len-1);
		Complex tA1=(a[i]+a[j].conj())*(Complex){0.5,0};
		Complex tA2=(a[i]-a[j].conj())*(Complex){0,-0.5};
		Complex tB1=(b[i]+b[j].conj())*(Complex){0.5,0};
		Complex tB2=(b[i]-b[j].conj())*(Complex){0,-0.5};
		A1[j]=tA1*tB1;A2[j]=tA1*tB2;
		B1[j]=tB1*tA2;B2[j]=tA2*tB2;
	}
	for(int i=0;i<len;++i){
		a[i]=A1[i]+A2[i]*(Complex){0,1};
		b[i]=B1[i]+B2[i]*(Complex){0,1};
	}
	FFT(a,len),FFT(b,len);
	for(int i=0;i<len;++i){
		int tA1=(ll)(a[i].r/len+0.5)%Mod;
		int tA2=(ll)(a[i].i/len+0.5)%Mod;
		int tB1=(ll)(b[i].r/len+0.5)%Mod;
		int tB2=(ll)(b[i].i/len+0.5)%Mod;
		C[i]=mod(((ll)tA1+((ll)(tA2+tB1)<<15)+((ll)tB2<<30))%Mod+Mod);
	}
}
void Integral(int A[],int B[],int n){for(int i=1;i<n;++i)B[i]=1ll*A[i-1]*inv[i]%Mod;B[0]=0;}
void Derivation(int A[],int B[],int n){for(int i=1;i<n;++i)B[i-1]=1ll*A[i]*i%Mod;B[n-1]=0;}
void Inverse(int A[],int B[],int n){
	if(n==1){B[0]=Pow(A[0],Mod-2);return;}
	Inverse(A,B,n>>1);
	MTT(A,B,t3,n);
	MTT(t3,B,t4,n);
	for(int i=0;i<n;i++)B[i]=mod(mod(B[i]+B[i])-t4[i]+Mod);
	for(int i=n;i<len;i++)B[i]=0;
}
void Logarithm(int A[],int B[],int n){
	Derivation(A,t1,n);
	Inverse(A,t2,n);
	MTT(t1,t2,t5,n);
	Integral(t5,B,n);
}
vector<int>Ans;
int main(){
	n=read(),Mod=read();
	Prepare(n+1);GetMu(len);
	for(int i=1;i<=n;++i)F[i]=read();
	F[0]=1;
	Logarithm(F,G,len);
	for(int i=1;i<=n;++i)F[i]=1ll*G[i]*i%Mod;
	for(int i=0;i<=n;i++)G[i]=0;
	for(int i=1;i<=n;i++){
		for(int j=1;1ll*i*j<=n;j++){
			G[i*j]=(G[i*j]+1ll*F[i]*mu[j]%Mod)%Mod;
		}
	}
	for(int i=1;i<=n;i++){
		G[i]=(G[i]%Mod+Mod)%Mod;
		if(G[i])Ans.push_back(i);
	}
	printf("%d\n",(int)(Ans.size()));
	for(auto x:Ans)printf("%d ",x);
	return 0;
}