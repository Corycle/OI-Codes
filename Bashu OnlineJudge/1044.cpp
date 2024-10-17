#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int n,m,a[105],f[105][10005];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	  scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
	  f[i][a[i]]=1;
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=m;j++)
	    f[i][j]+=f[i-1][j]+f[i-1][max(j-a[i],0)];
	printf("%d",f[n][m]);
	return 0; 
}