#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#include<complex>
#define ll long long
using namespace std;
const double pi=3.14159265358979323846264338327950288419716939937510;
const int inf=0x3f3f3f3f;
const int N=300005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,len=1;
complex<double>A[N],B[N],ft[N];
void FFT(complex<double>a[],int n,int ty){
	for(int i=0;i<n;i++){
		int j=0,k=i;
		for(int m=1;m<n;m<<=1){
			j=(j<<1)|(k&1);
			k>>=1;
		}
		if(i<j)swap(a[i],a[j]);
	}
	ft[0]=1;
	complex<double>t0,t1;
	for(int m=1;m<n;m<<=1){
		t0=exp(complex<double>(0,ty*pi/m));
		for(int i=1;i<=m;i++)ft[i]=ft[i-1]*t0;
		for(int k=0;k<n;k+=(m<<1)){
			for(int i=k;i<k+m;i++){
				t0=a[i];
				t1=a[i+m]*ft[i-k];
				a[i]=t0+t1;
				a[i+m]=t0-t1;
			}
		}
	}
	if(ty==1)return;
	t0=1.0/n;
	for(int i=0;i<n;i++)a[i]=a[i]*t0+0.5;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=0;i<n;i++){
		A[n-i-1]=read();
		B[i]=read();
	}
	while(len<n+n)len<<=1;
	FFT(A,len,1);FFT(B,len,1);
	for(int i=0;i<len;i++){
		A[i]=A[i]*B[i];
	}
	FFT(A,len,-1);
	for(int i=n-1;i>=0;i--){
		printf("%d\n",(int)A[i].real());
	}
	return 0;
}