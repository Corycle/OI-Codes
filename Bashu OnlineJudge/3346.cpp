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
const int inf=0x3f3f3f3f;
const double Pi=acos(-1);
const int N=200005;
const int M=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int R[N];
struct Number{
	int a[M];
	void Init(int n){
		memset(a,0,sizeof(a));
		while(n){
			a[++a[0]]=n%10;
			n/=10;
		}
	}
	void Print(){
		for(int i=a[0];i>=1;i--)printf("%d",a[i]);
		printf("\n");
	}
};
int cnt,vis[N],phi[N],prime[N];
void Prepare(int n){
	phi[1]=1;
	for(int i=2;i<=n;i++){
		if(!vis[i]){prime[++cnt]=i;phi[i]=i-1;}
		for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j])phi[i*prime[j]]=phi[i]*phi[prime[j]];
			else{phi[i*prime[j]]=phi[i]*prime[j];break;}
		}
	}
}
void FFT(complex<double>a[],int n,int f){
	for(int i=0;i<n;i++){
		if(i<R[i])swap(a[i],a[R[i]]);
	}
	for(int i=1;i<n;i<<=1){
		complex<double>Wn(cos(Pi/i),f*sin(Pi/i));
		for(int j=0;j<n;j+=(i<<1)){
			complex<double>W(1,0);
			for(int k=0;k<i;k++){
				complex<double>x=a[j+k],y=W*a[j+k+i];
				a[j+k]=x+y;a[j+k+i]=x-y;W*=Wn;
			}
		}
	}
	if(f==-1)for(int i=0;i<n;i++)a[i]/=n;
}
Number Multi(Number A,Number B){
	complex<double>a[N],b[N];
	int len=1,L=0;
	while(len<A.a[0]+B.a[0]){len<<=1;L++;}
	for(int i=0;i<len;i++){
		R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
		a[i]=0;b[i]=0;
	}
	for(int i=0;i<A.a[0];i++)a[i]=A.a[i+1];
	for(int i=0;i<B.a[0];i++)b[i]=B.a[i+1];
	FFT(a,len,1);FFT(b,len,1);
	for(int i=0;i<len;i++)a[i]*=b[i];
	FFT(a,len,-1);
	Number C;C.Init(0);
	for(int i=0;i<len;i++){
		C.a[i+1]=(int)(a[i].real()+0.5);
	}
	for(int i=1;i<=len;i++){
		C.a[i+1]+=C.a[i]/10;
		if(C.a[i]!=0)C.a[0]=i;
		C.a[i]%=10;
	}
	return C;
}
Number Mul(Number A,int b){
	Number B;B.Init(b);
	return Multi(A,B);
}
Number Pow(int y){
	Number ans;ans.Init(1);
	Number tot;tot.Init(2);
	while(y){
		if(y&1)ans=Multi(ans,tot);
		tot=Multi(tot,tot);
		y>>=1;
	}
	return ans;
}
Number Plas(Number A,Number B){
	A.a[0]=max(A.a[0],B.a[0]);
	for(int i=1;i<=A.a[0];i++)A.a[i]+=B.a[i];
	for(int i=1;i<=A.a[0];i++){
		A.a[i+1]+=A.a[i]/10;
		A.a[i]%=10;
		if(A.a[A.a[0]+1])A.a[0]++;
	}
	return A;
}
Number Division(Number A,int B){
	Number C;C.Init(0);int D=0;
	for(int i=A.a[0];i>=1;i--){
		D=D*10+A.a[i];
		C.a[i]=D/B;
		D%=B;
	}
	C.a[0]=A.a[0];
	while(C.a[0]&&!C.a[C.a[0]])C.a[0]--;
	return C;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int n=read();Prepare(n);
	Number Ans;Ans.Init(0);
	for(int i=1;i*i<=n;i++){
		if(n%i==0){
			int x=i,y=n/i;
			Ans=Plas(Ans,Mul(Pow(x),phi[y]));
			if(x!=y)Ans=Plas(Ans,Mul(Pow(y),phi[x]));
		}
	}
	Ans=Division(Ans,n);
	Ans.Print();
	return 0;
}