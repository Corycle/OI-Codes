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
const int M=20005;
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,s,a[N][N],f[N][M];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	s=read();n=read();m=read();
	for(int i=1;i<=s;i++){
		for(int j=1;j<=n;j++)a[j][i]=read();
	}
	for(int i=1;i<=n;i++)sort(a[i]+1,a[i]+s+1);
	for(int i=1;i<=n;i++){
		for(int j=0;j<=m;j++)f[i][j]=f[i-1][j];
		for(int k=1;k<=s;k++){
			int c=a[i][k]*2+1;
			for(int j=c;j<=m;j++){
				f[i][j]=max(f[i][j],f[i-1][j-c]+i*k);
			}
		}
	}
	printf("%d",f[n][m]);
	return 0;
}