/*
  组合数：杨辉三角 
  递推公式
      f[i][j]=f[i-1][j-1]+f[i-1][j]
*/ 
#include<cstdio>
#include<iostream>
#define Mod 100003
#define M 1010
using namespace std;
int f[M][M];
int main()
{
    int n,k;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
      f[i][0]=f[i][i]=1;
    for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
      {
          if(!f[i][j])
          f[i][j]=f[i-1][j-1]+f[i-1][j];
          f[i][j]%=Mod;
      }
    printf("%d",f[n][k]);
    return 0;
}