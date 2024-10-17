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
const int maxn=20;
const int N=105;
const int M=25;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
int c[N],p[N],h[N],f[N][N*N];
int w[N][N],g[N][N][M],tmp[N][N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	int C=read(),T=read();
	memset(g,-0x3f,sizeof(g));
	for(int i=1;i<=n;i++){
		p[i]=read();
		c[i]=read();
		g[i][i][0]=0;
	}
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		g[x][y][0]=max(g[x][y][0],z);
	}
	/*========Get_G========*/
	for(int t=1;t<=maxn;t++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				for(int k=1;k<=n;k++){
					g[i][j][t]=max(g[i][j][t],g[i][k][t-1]+g[k][j][t-1]);
				}
			}
		}
	}
	/*========Get_W========*/
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)w[i][j]=tmp[i][j]=-inf;
		int Lim=min(c[i],C); w[i][i]=tmp[i][i]=0;
		for(int t=0;t<=maxn;t++){
			if((Lim>>t)&1){
				for(int j=1;j<=n;j++){
					for(int k=1;k<=n;k++){
						w[i][j]=max(w[i][j],tmp[i][k]+g[k][j][t]);
					}
				}
				for(int j=1;j<=n;j++)tmp[i][j]=w[i][j];
			}
		}
		for(int j=1;j<=n;j++)w[i][j]=tmp[i][j];
	}
	/*========Get_F========*/
	for(int i=1;i<=n;i++)f[i][0]=0;
	for(int k=1;k<=n*n;k++){
		for(int i=1;i<=n;i++){
			if(k>=p[i]){
				for(int j=1;j<=n;j++){
					f[i][k]=max(f[i][k],f[j][k-p[i]]+w[i][j]);
				}
			}
		}
	}
	/*========Get_Ans========*/
	while(T--){
		int x=read(),q=read(),d=read();
		int l=0,r=q,Ans=q+1;
		while(l<=r){
			int mid=(l+r)>>1;
			if(f[x][mid]>=d){
				Ans=mid;
				r=mid-1;
			}
			else l=mid+1;
		}
		printf("%d\n",q-Ans);
	}
	return 0;
}