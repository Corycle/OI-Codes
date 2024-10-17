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
const int N=1005;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
int n,m;
int a[N][N],f[N][N],g[N][N],f1[N][N],f2[N][N];
int main(){
//	freopen("tower.in","r",stdin);
//	freopen("tower.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)for(int j=1;j<=i;j++)a[i][j]=read();
	for(int i=1;i<=n;i++)for(int j=1;j<=i;j++)f[i][j]=max(f[i-1][j-1],f[i-1][j])+a[i][j];
	for(int i=n;i>=1;i--)for(int j=1;j<=i;j++)g[i][j]=max(g[i+1][j+1],g[i+1][j])+a[i][j];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++)f1[i][j]=max(f1[i][j-1],f[i][j]+g[i][j]-a[i][j]);
		for(int j=i;j>=1;j--)f2[i][j]=max(f2[i][j+1],f[i][j]+g[i][j]-a[i][j]);
	}
	while(m--){
		int x=read(),y=read();
		if(x==1&&y==1)printf("-1\n");
		else printf("%d\n",max(f1[x][y-1],f2[x][y+1]));
	}
	return 0;
}