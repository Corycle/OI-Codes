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
const int N=400005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int R[N],X[N],Y[N];
int Sqr(int x){return x*x;}
void FFT(complex<double>a[],int n,int f){
	for(int i=0;i<n;i++)if(i<R[i])swap(a[i],a[R[i]]);
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
int n,m,c,sum,Ans;
complex<double>A[N],B[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		X[i]=read();
		Ans+=Sqr(X[i]);
		sum+=X[i];c-=X[i];
	}
	for(int i=1;i<=n;i++){
		Y[i]=read();
		Ans+=Sqr(Y[i]);
		sum-=Y[i];c+=Y[i];
	}
	c/=n;
	int Min=inf;
	Min=min(Min,n*Sqr(c)+2*sum*c);
	Min=min(Min,n*Sqr(c+1)+2*sum*(c+1));
	Min=min(Min,n*Sqr(c-1)+2*sum*(c-1));
	Ans+=Min;
	for(int i=1;i<=n;i++)X[i+n]=X[i];
	for(int i=1;i<=n/2;i++)swap(Y[i],Y[n-i+1]);
	int len=1,L=0;
	while(len<n*3){len<<=1;L++;}
	for(int i=0;i<len;i++){
		R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
	}
	for(int i=0;i<len;i++)A[i]=X[i+1];
	for(int i=0;i<len;i++)B[i]=Y[i+1];
	FFT(A,len,1);FFT(B,len,1);
	for(int i=0;i<len;i++)A[i]*=B[i];
	FFT(A,len,-1);
	int Max=0;
	for(int i=0;i<len;i++){
		Max=max(Max,(int)(A[i].real()+0.5));
	}
	Ans-=Max*2;
	printf("%d",Ans);
	return 0;
}