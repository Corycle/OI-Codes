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
int dp[35][35];
int main(){
	int i,j,k,m,n;
	scanf("%d%d",&n,&m);
	dp[0][1]=1;
	for(i=1;i<=m;i++){
		dp[i][1]=dp[i-1][2]+dp[i-1][n];
		dp[i][n]=dp[i-1][1]+dp[i-1][n-1];
		for(j=2;j<n;j++)
			dp[i][j]=dp[i-1][j-1]+dp[i-1][j+1];
	}
	printf("%d\n",dp[m][1]);
	return 0;
}