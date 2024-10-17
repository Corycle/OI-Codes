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
const int N=2000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int R[N];
complex<double>A[N],B[N],Ans[N];
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
char s1[N],s2[N];
int n,m,cnt,Sa[N],Sb[N],q[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();scanf("%s%s",s1+1,s2+1);
	for(int i=1;i<=n/2;i++)swap(s1[i],s1[n-i+1]);
	for(int i=1;i<=n;i++)Sa[i]=('a'<=s1[i]&&s1[i]<='z')?s1[i]-'a'+1:0;
	for(int i=1;i<=m;i++)Sb[i]=('a'<=s2[i]&&s2[i]<='z')?s2[i]-'a'+1:0;
	int len=1,L=0;
	while(len<n+m){len<<=1;L++;}
	for(int i=0;i<len;i++){
		R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
	}
	
	for(int i=0;i<len;i++){A[i]=Sa[i+1]*Sa[i+1]*Sa[i+1];}
	for(int i=0;i<len;i++){B[i]=Sb[i+1];}
	FFT(A,len,1);FFT(B,len,1);
	for(int i=0;i<len;i++)Ans[i]+=A[i]*B[i];
	
	for(int i=0;i<len;i++){A[i]=Sa[i+1];}
	for(int i=0;i<len;i++){B[i]=Sb[i+1]*Sb[i+1]*Sb[i+1];}
	FFT(A,len,1);FFT(B,len,1);
	for(int i=0;i<len;i++)Ans[i]+=A[i]*B[i];
	
	for(int i=0;i<len;i++){A[i]=Sa[i+1]*Sa[i+1];}
	for(int i=0;i<len;i++){B[i]=Sb[i+1]*Sb[i+1];}
	FFT(A,len,1);FFT(B,len,1);
	for(int i=0;i<len;i++)Ans[i]-=A[i]*B[i]*2.0;
	
	FFT(Ans,len,-1);
	for(int i=n-1;i<m;i++){
		int p=(int)(Ans[i].real()+0.5);
		if(p==0)q[++cnt]=i-(n-2);
	}
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++)printf("%d ",q[i]);
	return 0;
}