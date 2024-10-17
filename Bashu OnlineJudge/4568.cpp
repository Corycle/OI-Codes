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
#define y1 y_1
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,Q,a[N][N],sum[3][N][N];
int Sum(int i,int x1,int y1,int x2,int y2){
	if(x1>x2||y1>y2)return 0;
	return sum[i][x2][y2]-sum[i][x2][y1-1]-sum[i][x1-1][y2]+sum[i][x1-1][y1-1];
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Q=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=m;j++)a[i][j]=s[j]-'0';
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)sum[0][i][j]=sum[0][i-1][j]+sum[0][i][j-1]-sum[0][i-1][j-1]+a[i][j];
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)sum[1][i][j]=sum[1][i-1][j]+sum[1][i][j-1]-sum[1][i-1][j-1]+(a[i][j]&a[i][j-1]);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)sum[2][i][j]=sum[2][i-1][j]+sum[2][i][j-1]-sum[2][i-1][j-1]+(a[i][j]&a[i-1][j]);
	while(Q--){
		int x1=read(),y1=read(),x2=read(),y2=read();
		int V=Sum(0,x1,y1,x2,y2),E=Sum(1,x1,y1+1,x2,y2)+Sum(2,x1+1,y1,x2,y2);
		printf("%d\n",V-E);
	}
	return 0;
}