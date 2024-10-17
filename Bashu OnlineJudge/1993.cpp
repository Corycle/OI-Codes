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
int n,m;
int a[N],f[N][N];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	memset(f,0x3f,sizeof(f));
	for(int i=n;i>=1;i--)a[i]=read();
	f[2][1]=abs(a[2]-a[1]);
	for(int i=3;i<=n;i++){
		for(int j=1;j<=i-2;j++)f[i][j]=f[i-1][j]+abs(a[i]-a[i-1]);
		for(int j=1;j<=i-2;j++)f[i][i-1]=min(f[i][i-1],f[i-1][j]+abs(a[i]-a[j]));
	}
	int ans=inf;
	for(int i=1;i<n;i++){
		ans=min(ans,f[n][i]);
	}
	printf("%d",ans);
	return 0;
}