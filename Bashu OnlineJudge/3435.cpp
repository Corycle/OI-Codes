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
const int N=305;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,f[N][N],g[N][N][N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int val=read(),l=read(),r=read();
		for(int j=l;j<=r;j++)g[j][l][r]=max(g[j][l][r],val);
	}
	for(int l=n;l>=1;l--){
		for(int r=l;r<=n;r++){
			for(int k=l;k<=r;k++)g[k][l][r]=max(g[k][l][r],max(g[k][l][r-1],g[k][l+1][r]));
		}
	}
	for(int l=n;l>=1;l--){
		for(int r=l;r<=n;r++){
			for(int k=l;k<r;k++)f[l][r]=max(f[l][r],f[l][k]+f[k+1][r]);
			for(int k=l;k<=r;k++)f[l][r]=max(f[l][r],f[l][k-1]+f[k+1][r]+g[k][l][r]);
		}
	}
	printf("%d\n",f[1][n]);
	return 0;
}
