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
const int N=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
int a[N],sum[N][N],f[N][N],Max[N][N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read()+1;
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			sum[i][j]=sum[i][j-1]+a[j];
			Max[i][j]=max(Max[i][j-1],a[j]);
		}
	}
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=n;i++)f[i][1]=Max[1][i]*i-sum[1][i];
	for(int j=1;j<=m;j++){
		for(int i=1;i<=n;i++){
			for(int k=1;k<i;k++){
				int dlt=Max[k+1][i]*(i-k)-sum[k+1][i];
				f[i][j]=min(f[i][j],f[k][j-1]+dlt);
			}
		}
	}
	int ans=inf;
	for(int i=1;i<=m;i++){
		ans=min(ans,f[n][i]);
	}
	printf("%d",ans);
	return 0;
}