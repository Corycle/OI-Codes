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
char s[N];
ll ans[N][N];
int n,m,K,a[N],sum[N][N];
int main(){
//	freopen("bear.in","r",stdin);
//	freopen("bear.out","w",stdout);
	n=read();m=read();K=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=m;j++)sum[i][j]=sum[i-1][j]+(s[j]=='H');
	}
	for(int t=1;t<=n;t++){
		for(int l=1;l+t-1<=n;l++){
			int r=l+t-1;
			for(int i=1,j=0;i<=m;i++){
				a[i]=a[i-1]+sum[r][i]-sum[l-1][i];
				while(a[i]-a[j+1]>=K)j++;
				if(a[i]>=K){ans[t][i-j]++;ans[t][i+1]--;}
			}
		}
		for(int i=1;i<=m;i++)ans[t][i]+=ans[t][i-1];
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)ans[i][j]+=ans[i-1][j]+ans[i][j-1]-ans[i-1][j-1];
	int T=read();while(T--){int x=read(),y=read();printf("%lld\n",ans[x][y]);}
	return 0;
}