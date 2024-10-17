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
const int N=2005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
complex<double>W[N],P[N];
void FFT(complex<double>a[],complex<double>b[],int f){
	complex<double> *w=(f==1?W:P);
	for(int i=0;i<n;i++){
		complex<double>Wn=w[0];
		for(int j=0;j<n;j++){
			b[i]+=a[j]*Wn;
			Wn*=w[i];
		}
	}
	if(f==-1)for(int i=0;i<n;i++)b[i]/=n;
}
complex<double>a[N],b[N],c[N];
complex<double>A[N],B[N],C[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=0;i<n;i++){
		double x;
		if(i==0){
			for(int j=0;j<n;j++){
				scanf("%lf",&x);
				a[j]=complex<double>(x,0);
			}
		}
		else for(int j=0;j<n;j++)scanf("%lf",&x); 
	}
	for(int i=0;i<n;i++){
		double x;
		scanf("%lf",&x);
		b[i]=complex<double>(x,0);
	}
	W[0]=P[0]=1;
	complex<double>Wn1(cos(2*Pi/n),sin(2*Pi/n));
	complex<double>Wn2(cos(2*Pi/n),-sin(2*Pi/n));
	for(int i=1;i<n;i++){
		W[i]=W[i-1]*Wn1;
		P[i]=P[i-1]*Wn2;
	}
	b[n]=b[0];
	for(int i=0;i<n;i++)b[i]=b[i+1];
	FFT(a,A,1);FFT(b,B,1);
	for(int i=0;i<n;i++)C[i]=B[i]/A[i];
	FFT(C,c,-1);
	for(int i=n-1;i>=0;i--)printf("%.2lf\n",c[i].real());
	return 0;
}