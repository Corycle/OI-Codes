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
const int Mod=100000001;
const int N=10000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
double Ans;
int n,m,A,B,C,a[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();A=read();B=read();C=read();a[1]=read();
	for(int i=2;i<=n;i++)a[i]=(1ll*a[i-1]*A+B)%Mod;
	for(int i=1;i<=n;i++)a[i]=a[i]%C+1;a[0]=a[n];
	for(int i=1;i<=n;i++){
		double p=(double)min(a[i-1],a[i])/(1ll*a[i-1]*a[i]);
		Ans=Ans*(1-p)+(Ans+1)*p;
	}
	printf("%.3lf",Ans);
	return 0;
}