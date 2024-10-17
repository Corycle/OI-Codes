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
const int N=105;
const int M=15;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,K;
int f1[N][M],f2[N][N][M];
int a[N][M],sum1[N],sum2[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();K=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=read();
			if(j==1)sum1[i]=sum1[i-1]+a[i][j];
			if(j==2)sum2[i]=sum2[i-1]+a[i][j];
		}
	}
	if(m==1){
		for(int k=1;k<=K;k++){
			for(int i=1;i<=n;i++){
				f1[i][k]=f1[i-1][k];
				for(int j=0;j<i;j++){
					f1[i][k]=max(f1[i][k],f1[j][k-1]+sum1[i]-sum1[j]);
				}
			}
		}
		printf("%d",f1[n][K]);
	}
	if(m==2){
		for(int k=1;k<=K;k++){
			for(int i=1;i<=n;i++){
				for(int j=1;j<=n;j++){
					f2[i][j][k]=max(f2[i-1][j][k],f2[i][j-1][k]);
					for(int l=0;l<i;l++)f2[i][j][k]=max(f2[i][j][k],f2[l][j][k-1]+sum1[i]-sum1[l]);
					for(int l=0;l<j;l++)f2[i][j][k]=max(f2[i][j][k],f2[i][l][k-1]+sum2[j]-sum2[l]);
					if(i==j)for(int l=0;l<i;l++)f2[i][j][k]=max(f2[i][j][k],f2[l][l][k-1]+sum1[i]-sum1[l]+sum2[j]-sum2[l]);
				}
			}
		}
		printf("%d",f2[n][n][K]);
	}
	return 0;
}