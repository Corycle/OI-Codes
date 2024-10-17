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
const int N=55;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,a[N],f[N][N][N][N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=50;memset(f,-0x3f,sizeof(f));
	for(int i=1;i<=n;i++){a[i]=read();f[i][i][a[i]][a[i]]=1;}
	for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)f[i][j][min(a[i],a[j])][max(a[i],a[j])]=2;
	for(int i=n;i>=1;i--){
		for(int j=i;j<=n;j++){
			for(int l=m;l>=1;l--){
				for(int r=l;r<=m;r++){
					f[i][j][l][r]=max(f[i][j][l][r],f[i][j][l+1][r]);
					f[i][j][l][r]=max(f[i][j][l][r],f[i][j][l][r-1]);
					f[i][j][l][r]=max(f[i][j][l][r],f[i+1][j][l][r]+(a[i]==l));
					f[i][j][l][r]=max(f[i][j][l][r],f[i][j-1][l][r]+(a[j]==r));
					f[i][j][l][r]=max(f[i][j][l][r],f[i+1][j-1][l][r]+(a[i]==r)+(a[j]==l));
				}
			}
		}
	}
	printf("%d\n",f[1][n][1][m]);
	return 0;
}
