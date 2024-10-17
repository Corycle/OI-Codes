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
typedef long long LL;
int dp[100010];
int main()
{
    int n,k,i,j;
    scanf("%d%d",&n,&k);
    for(i=1;i<=k;i++)dp[i]=1;
    for(i=2;i<=n;i++){
        for(j=1;j<=k&&j<=i;j++){
            dp[i]=(dp[i]+dp[i-j])%100003;
        }
    }
    printf("%d\n",dp[n]);
    return 0;
}