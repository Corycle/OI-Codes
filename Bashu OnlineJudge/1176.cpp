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
int n,s;
double f[N][N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();s=read();
	for(int i=n;i>=0;i--){
		for(int j=s;j>=0;j--){
			if(i==n&&j==s)continue;
			double P1=(double)(i*j)/(n*s);
			double P2=(double)((n-i)*j)/(n*s);
			double P3=(double)(i*(s-j))/(n*s);
			double P4=(double)((n-i)*(s-j))/(n*s);
			f[i][j]=(P2*f[i+1][j]+P3*f[i][j+1]+P4*f[i+1][j+1]+1)/(1-P1);
		}
	}
	printf("%.4lf",f[0][0]);
	return 0;
}