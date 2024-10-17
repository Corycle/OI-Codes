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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n;
int a[N],f[N][N],g[N][N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			g[i][j]=g[i][j-1]+(a[j]!=j-i);
		}
	}
	f[0][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			for(int k=0;k<i;k++){
				f[i][j]=min(f[i][j],f[k][j-1]+g[k+1][i]);
			}
		}
	}
	for(int i=1;i<=n;i++)printf("%d\n",f[n][i]);
	return 0;
}