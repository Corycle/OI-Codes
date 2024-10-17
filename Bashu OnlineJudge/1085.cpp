#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<iostream>
#define max(a,b) a>b?a:b
#define debug(x) cout<<#x<<x<<endl;
#define debug1d(a,n)for(int i=1;i<=n;i++)cout<<"a["<<i<<"]="<<a[i]<<endl;
using namespace std;
int f,v,a[105][105],dp[105][105],pre[105][105],pos[105],maxx;
//a:?i?????j??????
//pre:dp[i][j]?,?????????
//pos:????,???? 
void input()//?? 
{
    scanf("%d%d",&f,&v);
    int i,j;
    for(i=1;i<=f;i++)
     for(j=1;j<=v;j++)scanf("%d",&a[i][j]);
}

int main()
{
    int i;
    input();
    {
    int i,j,k;
    j=1;
    memset(pre,0,sizeof(pre));
    for(i=1;i<=f;i++)
     for(j=1;j<=v;j++)
      dp[i][j]=-32767;
    for(i=1;i<=f;i++)dp[0][i]=0;
    //?????? 
      
      
    //???? 
    for(i=1;i<=f;i++)
     for(j=i;j<=v;j++)
      {
           for(k=i-1;k<j;k++)
           if(dp[i][j]<dp[i-1][k]+a[i][j])
            {
                dp[i][j]=dp[i-1][k]+a[i][j];
                pre[i][j]=k;
            }
          
      }
    //????? 
}
    
    
    maxx=-32767;
    for(i=1;i<=v;i++)
    {
        if(dp[f][i]>maxx){
            pos[f]=i;
            maxx=dp[f][i];
        }
    }
    //?????????????? 
    
    printf("%d ",maxx);printf("\n");
    //?????????????????? 
    for(i=f;pre[i][pos[i]]!=0;i--)
    {
        pos[i-1]=pre[i][pos[i]];
    }
    for(int i=1;i<=f;i++){
     printf("%d ",pos[i]);
    }
    return 0;
}