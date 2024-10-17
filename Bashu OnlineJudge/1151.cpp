#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
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
int n,m,a[N],c[N][N];
int f[N][N],p[N][N],g[N][N];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	while(1){
		n=read();m=read()+1;
		if(n+m==1)break;
		memset(a,0,sizeof(a));
		memset(c,0,sizeof(c));
		memset(g,0,sizeof(g));
		memset(p,0,sizeof(p));
		memset(f,0x3f,sizeof(f));
		for(int i=1;i<=n;i++){
			a[i]=g[i][i]=read();
		}
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				g[i][j]=g[i][j-1]+a[j];
				c[i][j]=c[i][j-1]+a[j]*g[i][j-1];
			}
		}
		for(int i=1;i<=n;i++)f[i][1]=c[1][i];
		for(int i=1;i<=n;i++){
			int t=min(i,m);
			for(int j=t;j>=2;j--){
				int l=p[i-1][j],r=p[i][j+1];
				if(!r)r=i-1;
				for(int k=l;k<=r;k++){
					if(f[i][j]>=f[k][j-1]+c[k+1][i]){
						f[i][j]=f[k][j-1]+c[k+1][i];
						p[i][j]=k;
					}
				}
			}
		}
		printf("%d\n",f[n][m]);
	}
	return 0;
}