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
int n,m,l,r,V,v[N];
double f[N][N],sum[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();l=read();r=read();V=read();
	for(int i=1;i<=n;i++)v[i]=read();
	f[n+1][m]=V;
	for(int i=n;i>=1;i--){
		sum[0]=f[i+1][0];
		for(int j=1;j<=m;j++)sum[j]=sum[j-1]+f[i+1][j];
		for(int j=0;j<=m;j++){
			f[i][j]=f[i+1][j]+v[i];
			if(j+r<=m)f[i][j]=max(f[i][j],(sum[j+r]-sum[j+l-1])/(r-l+1));
			else if(j+l<=m)f[i][j]=max(f[i][j],(sum[m]-sum[j+l-1]+f[i+1][m]*(j+r-m))/(r-l+1));
			else f[i][j]=max(f[i][j],f[i+1][m]);
		}
		/*
		for(int j=0;j<=m;j++){
			double sum=0;
			f[i][j]=f[i+1][j]+v[i];
			for(int k=l;k<=r;k++){
				sum+=f[i+1][min(j+k,m)];
			}
			sum=sum/(r-l+1);
			f[i][j]=max(f[i][j],sum);
		}
		*/
	}
	printf("%.3lf",f[1][0]);
	return 0;
}