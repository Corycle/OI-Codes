#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
using namespace std;
int m,n,a[51][51],F[100][51][51];
int Max(int a,int b,int c,int d)
{
    if(a>=b&&a>=c&&a>=d)
        return a;
    if(b>=a&&b>=c&&b>=d)
        return b;
    if(c>=a&&c>=b&&c>=d)
        return c;
    if(d>=a&&d>=b&&d>=c)
        return d;
}
void read()
{
    int i,j;
    cin>>n>>m;
    for (i=1;i<=n;i++)
        for (j=1;j<=m;j++)
        cin>>a[i][j];
    return;
}
void dp()
{
    int i,j,k;
    for(k=1;k<=n+m-2;k++)
    	for(i=1;i<=n;i++)
      		for(j=1;j<=n;j++){
        	    if(i==n&&j==n&&k==n+m-2||i!=j&&k+2-i>=1&&k+2-j>=1)
           		F[k][i][j]=Max(F[k-1][i-1][j],F[k-1][i][j-1],F[k-1][i][j],F[k-1][i-1][j-1])+a[i][k+2-i]+a[j][k+2-j];
        	}
    cout<<F[n+m-2][n][n];
}
int main(){
    read();
    dp();
    return 0;
}