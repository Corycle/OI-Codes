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
const int N=5005;
const int M=2005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
int a[N],c[N][N],f[N][M],p[N][M];
/*
	f[i][j]=min(f[i][j],f[k][j-1]+c[k+1][i]);
	f[][]的两维反过来
	f[j][i]=min(f[j][i],f[j-1][k]+c[k+1][i]);
	区间DP的形式了用四边形不等式去优化
*/
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			c[i][j]=c[i][j-1]+a[j]-a[(i+j)/2];
		}
	}
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=n;i++)f[i][1]=c[1][i];
	for(int i=1;i<=n;i++){
		for(int j=min(i,m);j>=2;j--){
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
	printf("%d",f[n][m]);
	return 0;
}