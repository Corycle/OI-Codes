#include<iostream>
#include<iomanip>
#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<map>
using namespace std;
int n,m;
double a[85][85];
double f[85][25],la[25],re[85][25],pre[85][25];
void out(int x,int y)
{
	if(x==1&&y==0)
	{
		printf("1");
		return ;
	}	
	else out(re[x][y],pre[x][y]);
	printf("->%d",x);
}
int main()
{
	scanf("%d%d",&n,&m);
	la[0]=1;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	{
		scanf("%lf",&a[i][j]);
	}
	for(int i=1;i<=n;i++)
	for(int j=0;j<=m;j++) f[i][j]=100000000.0;
	for(int i=1;i<=m;i++) la[i]=la[i-1]*0.5,f[1][i]=0;
	f[1][0]=0;
	for(int j=0;j<=m;j++)
	{
		for(int q=1;q<=n;q++)
		for(int i=2;i<=n;i++)
		{
			for(int k=1;k<=n;k++)
			for(int l=0;l<j;l++)
			{
				if(a[k][i]!=0&&f[k][l]!=100000000.0&&f[k][l]+a[k][i]*la[j-l]<f[i][j]) f[i][j]=f[k][l]+a[k][i]*la[j-l],re[i][j]=k,pre[i][j]=l;
			}
		}
		for(int q=1;q<=n;q++)
		for(int i=2;i<=n;i++)
		{
			for(int k=1;k<=n;k++)
			{
				if(i==k) continue;
				if(a[k][i]!=0&&f[k][j]+a[k][i]<f[i][j]) f[i][j]=f[k][j]+a[k][i],re[i][j]=k,pre[i][j]=j;
			}
		}
	}
	printf("%0.2lf\n",f[n][m]);
	out(n,m);
	return 0;
}