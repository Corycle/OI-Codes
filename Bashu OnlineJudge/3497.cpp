#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,a[105][105],pre[105],t,dis[105],ans1,ans2;
bool b[105];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        a[x][y]=z;//无向图
        a[y][x]=z;//x到y，y到x，都要存
    }
    memset(dis,127,sizeof(dis));//dijkstra模版，只是多存个路径
    t=1;pre[1]=0;b[1]=1;dis[1]=0;
    for(int i=1;i<n;i++)
    {
        for(int j=1;j<=n;j++)
            if(a[t][j]>0&&dis[t]+a[t][j]<dis[j]){dis[j]=dis[t]+a[t][j];pre[j]=t;}
        int x=0x7fffffff;
        for(int j=1;j<=n;j++)
            if(dis[j]<x&&!b[j]){x=dis[j];t=j;}
        b[t]=1;
    }
    ans1=dis[n];
    int p=n;
    while(pre[p]!=0)//已知循环次数可以不用dfs
    {
        a[p][pre[p]]*=2;
        a[pre[p]][p]*=2;
        memset(dis,127,sizeof(dis));
        memset(b,0,sizeof(b));
        t=1;b[1]=1;dis[1]=0;
        for(int i=1;i<n;i++)
        {
            for(int j=1;j<=n;j++)
                if(a[t][j]>0&&dis[t]+a[t][j]<dis[j])dis[j]=dis[t]+a[t][j];
            int x=0x7fffffff;
            for(int j=1;j<=n;j++)
                if(dis[j]<x&&!b[j]){x=dis[j];t=j;}
            b[t]=1;
        }
        ans2=max(ans2,dis[n]);
        a[p][pre[p]]/=2;//类似dfs回溯
        a[pre[p]][p]/=2;
        p=pre[p];
    }
    printf("%d",ans2-ans1);
}