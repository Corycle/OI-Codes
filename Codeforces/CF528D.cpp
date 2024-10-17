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
const double Pi=acos(-1);
const int N=600005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N],t[N];
int n,m,K,Ans,len,L,R[N],cnt[N];
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
complex<double>A[N],B[N];
void Solve(char c){
	for(int i=0;i<len;i++)A[i]=B[i]=0;
	for(int i=0,j=-inf;i<n;i++){
		if(s[i]==c)j=i;
		if(i-j<=K)A[i]=1;
	}
	for(int i=n-1,j=inf;i>=0;i--){
		if(s[i]==c)j=i;
		if(j-i<=K)A[i]=1;
	}
	for(int i=0;i<m;i++)B[i]=(t[m-i-1]==c);
	FFT(A,len,1);FFT(B,len,1);
	for(int i=0;i<len;i++)A[i]=A[i]*B[i];
	FFT(A,len,-1);
	for(int i=0;i<len;i++)cnt[i]+=(int)(A[i].real()+0.5);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();K=read();
	scanf("%s%s",s,t);
	
	len=1;L=0;
	while(len<n+n){len<<=1;L++;}
	for(int i=0;i<len;i++){
		R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
	}
	
	Solve('A');Solve('T');
	Solve('G');Solve('C');
	for(int i=0;i<len;i++)Ans+=(cnt[i]==m);
	printf("%d",Ans);
	return 0;
}
