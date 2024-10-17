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
const double pi=3.1415926;
const int inf=0x3f3f3f3f;
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s1[N],s2[N];
complex<double>A[N],B[N],ft[N];
int ans[N],len=1,len1,len2;
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
	int n=read();
	scanf("%s%s",s1+1,s2+1);
	for(int i=n;i>=1;i--){
		A[len1++]=s1[i]-'0';
		B[len2++]=s2[i]-'0';
	}
	while(len<n+n)len<<=1;
//	cout<<len<<endl;
	FFT(A,len,1);
	FFT(B,len,1);
	for(int i=0;i<len;i++){
		A[i]=A[i]*B[i];
	}
	FFT(A,len,-1);
	for(int i=0;i<len;i++){
		ans[i]=(int)A[i].real();
	}
	for(int i=0;i<len;i++){
		ans[i+1]+=ans[i]/10;
		ans[i]%=10;
	}
	while(len&&!ans[len])len--;
	for(int i=len;i>=0;i--)printf("%d",ans[i]);
	return 0;
}
