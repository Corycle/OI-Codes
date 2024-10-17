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
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
double f0,f1,g0,g1;
double g[N],f[N][2];
int main(){
//	freopen("ring.in","r",stdin);
//	freopen("ring.out","w",stdout);
	n=read();m=read();g[1]=1;
	for(int i=2;i<=n;i++)g[i]=g[i-1]/m;
	for(int i=2;i<n;i++)g[i]*=i;
	for(int i=2;i<=n;i++){
		f[i][0]=(g[i-1]*(i-1)*(m-1)+f0*(m-2)+f1*(m-1))/m;
		f[i][1]=f0/m;
		f0=(f0+g0)/m+f[i][0];
		f1=(f1+g1)/m+f[i][1];
		g0=g0/m+f[i][0];
		g1=g1/m+f[i][1];
	}
	printf("%.5lf",g[n]*n+f0);
	return 0;
}