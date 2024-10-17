#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
struct tmp
{
    int a,b;
}dp[20005];
int f[20005];
bool cmp(tmp x,tmp y)
{
    return x.a<y.a;
}
int main()
{
    int t,n,maxx,i,j;
    int a[20005];
    memset(a,0,sizeof(a));
    memset(dp,0,sizeof(dp));
        cin>>n;
    for(i=1;i<=n;i++)
    {
    cin>>dp[i].a>>dp[i].b;
               f[i]=1;
            }
    sort(dp+1,dp+n+1,cmp);//排序 以a为主 
    maxx=-10000;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=i-1;j++)
        {
            if(dp[j].b<dp[i].b)f[i]=max(f[j]+1,f[i]);
        }
    }
    for(i=1;i<=n;i++)maxx=max(maxx,f[i]);   
    cout<<maxx<<endl;
    return 0;
}