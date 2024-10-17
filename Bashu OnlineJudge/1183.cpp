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
const int N=5005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
double f[N][N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=0;i<=n;i++){
		for(int j=0;j<=m;j++){
			int num=i+j;
			if(i)f[i][j]+=(f[i-1][j]+1)*i/num;
			if(j)f[i][j]+=(f[i][j-1]-1)*j/num;
			f[i][j]=max(f[i][j],0.0);
		}
	}
	printf("%.6lf",(ll)(f[n][m]*1e6)/1e6);
	return 0;
}