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
const int N=300005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int R[N];
complex<double>A[N],B[N],C[N],D[N];
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
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int n=0;read();
	int len=1,L=0,m=0,x;
	while(scanf("%d",&x)!=EOF){
		n++;
		A[x*1]+=1;
		B[x*2]+=1;
		C[x*3]+=1;
		m=max(m,x*3);
	}
	/*
		ans=A[x]/(1!)+(A[x]*A[x]-B[x])/(2!)+(A[x]*A[x]*A[x]-3*A[x]*B[x]+2*C[x])/(3!);
	*/
	while(len<m){len<<=1;L++;}
	for(int i=0;i<len;i++){
		R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
	}
	FFT(A,len,1);FFT(B,len,1);
	for(int i=0;i<len;i++){
		D[i]=(A[i]*A[i]*A[i])/6.0+(A[i]*A[i]-A[i]*B[i]-B[i])/2.0+A[i];
	}
	FFT(D,len,-1);
	for(int i=0;i<len;i++)D[i]+=C[i]/3.0;
	for(int i=0;i<len;i++){
		int x=(int)(D[i].real()+0.5);
		if(x)printf("%d %d\n",i,x);
	}
	return 0;
}