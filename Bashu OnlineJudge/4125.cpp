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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int ans[N],R[N];
char s1[N],s2[N];
complex<double>A[N],B[N];
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
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int n=read(),len=1,L=0;
	scanf("%s%s",s1+1,s2+1);
	for(int i=0;i<n;i++)A[i]=s1[n-i]-'0';
	for(int i=0;i<n;i++)B[i]=s2[n-i]-'0';
	while(len<n+n){len<<=1;L++;}
	for(int i=0;i<len;i++){
		R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
	}
	FFT(A,len,1);FFT(B,len,1);
	for(int i=0;i<len;i++)A[i]*=B[i];
	FFT(A,len,-1);
	for(int i=0;i<len;i++){
		ans[i]=(int)(A[i].real()+0.1);
	}
	for(int i=0;i<len;i++){
		ans[i+1]+=ans[i]/10;
		ans[i]%=10;
	}
	while(len&&!ans[len])len--;
	for(int i=len;i>=0;i--)printf("%d",ans[i]);
	return 0;
}