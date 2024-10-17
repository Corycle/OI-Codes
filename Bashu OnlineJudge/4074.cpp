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
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
double g[N],f[N][2];
int main(){
//	freopen("ring.in","r",stdin);
//	freopen("ring.out","w",stdout);
	n=read();m=read();
	g[1]=f[0][1]=1;
	for(int i=2;i<=n;i++)g[i]=g[i-1]/m;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=i;j++){
			f[i][0]+=g[i-j]*(i-j)*(f[j][0]/m*(m-2)+f[j][1]/m*(m-1));
			f[i][1]+=g[i-j]*(i-j)*(f[j][0]/m);
		}
	}
	double ans=g[n]*n;
	for(int i=1;i<=n;i++){
		ans+=g[i]*i*i*f[n-i][0];
	}
	printf("%.5lf",ans);
	return 0;
}