#include <iostream>
#include <cstring>
using namespace std;
int a[2502][2502],l[2502][2502],u[2502][2502],f[2502][2502];
int main()
{
    std::ios::sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        a[i][0]=1;
        a[i][m+1]=1;
    }
    for(int i=1;i<=m;i++)
    {
        a[0][i]=1;
    }//封起来，防止越界
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>a[i][j];
            if(a[i][j-1]==0)l[i][j]=l[i][j-1]+1;//列
            else l[i][j]=0;
            if(a[i-1][j]==0)u[i][j]=u[i-1][j]+1;//行
            else u[i][j]=0;
        }
    }
    int ans=0;

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(a[i][j]==1)
            {
                f[i][j]=min(min(f[i-1][j-1],l[i][j]),u[i][j])+1;
            }
            else f[i][j]=0;
            ans=max(ans,f[i][j]);
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=m;j>=1;j--)
        {
            if(a[i][j+1]==0)
            {
                l[i][j]=l[i][j+1]+1;//换一个方向，斜向左
            }
            else l[i][j]=0;
        }
    }
    memset(f,0,sizeof(f));
    for(int i=1;i<=n;i++)
    {
        for(int j=m;j>=1;j--)
        {
            if(a[i][j]==1)f[i][j]=min(min(f[i-1][j+1],l[i][j]),u[i][j])+1;
            else f[i][j]=0;
            ans=max(ans,f[i][j]);
        }
    }
    cout<<ans<<endl;
    return 0;
}