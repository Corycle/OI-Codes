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
const int N=1e5+5;
const int M=27;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,K,a[N],f[N],g[M][M],sum[M][N],Min[M][N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	memset(f,0x3f,sizeof(f));
	memset(Min,0x3f,sizeof(Min));
	n=read();m=read();K=read();scanf("%s",s+1);
	for(int i=1;i<=n;i++)a[i]=s[i]-'a'+1;
	for(int i=1;i<=m;i++)for(int j=1;j<=m;j++)g[i][j]=read();
	for(int k=1;k<=m;k++)for(int i=1;i<=m;i++)for(int j=1;j<=m;j++)g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
	for(int k=1;k<=m;k++)for(int i=1;i<=n;i++){sum[k][i]=sum[k][i-1]+g[a[i]][k];if(i>=K)f[i]=min(f[i],sum[k][i]);}
	for(int i=K;i<K*2&&i<=n;i++)for(int k=1;k<=m;k++)Min[k][i]=min(f[i]-sum[k][i],Min[k][i-1]);
	for(int i=K*2;i<=n;i++){
		for(int k=1;k<=m;k++)f[i]=min(f[i],sum[k][i]+Min[k][i-K]);
		for(int k=1;k<=m;k++)Min[k][i]=min(f[i]-sum[k][i],Min[k][i-1]);
	}
	printf("%d\n",f[n]);
	return 0;
}
