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
const int N=4005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
int a[N],s[N],c[N],t[N],f[N][N];
int main(){
//	freopen("show.in","r",stdin);
//	freopen("show.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)s[i]=read();
	for(int i=1;i<=n+m;i++)c[i]=read();
	t[0]=n;
	for(int i=1;i<=n;i++)t[i]=t[i-1]>>1;
	for(int i=0;i<=n+m;i++){
		for(int j=1;j<=n;j++)f[i][j]=-inf;
	}
	for(int i=n;i>=1;i--){
		int x=a[i];
		for(int j=n;j>=1;j--){
			f[x][j]=max(f[x][j],f[x][j-1]+c[x]-s[i]);
		}
		for(int j=x;j<=n+m;j++){
			for(int k=0;k<=t[j-x];k++){
				f[j+1][k/2]=max(f[j+1][k/2],f[j][k]+(k/2)*c[j+1]);
			}
		}
	}
	printf("%d",f[n+m][0]);
	return 0;
}