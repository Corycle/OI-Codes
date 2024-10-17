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
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
double a[N][N][3],f[N][N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int k=0;k<3;k++){
				scanf("%lf",&a[i][j][k]);
			}
		}
	}
	for(int i=n;i>=1;i--){
		for(int j=m;j>=1;j--){
			double P1=a[i][j][0];
			double P2=a[i][j][1];
			double P3=a[i][j][2];
			f[i][j]=(P2*f[i][j+1]+P3*f[i+1][j]+2)/(1-P1);
			if(i==n&&j==m)f[i][j]=0;
		}
	}
	printf("%.3lf",f[1][1]);
	return 0;
}