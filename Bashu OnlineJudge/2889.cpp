#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
#define MAXN 45011
#define INF 100000
using namespace std;
int n,m,tot,fa[305],ma,mi,ans,j,cnt;
//bool flag[MAXN];
struct Node
{
    int u,v,w,next;
}edge[MAXN];
inline bool cmp(Node a,Node b)
{
    return a.w<b.w;
}
inline int find(int a)
{
    if(fa[a]!=a)return find(fa[a]);
    else return fa[a];
}
int main()
{
    //freopen("tree.in","r",stdin);
    //freopen("tree.out","w",stdout);
    scanf("%d%d",&n,&m);
    ans=INF;
    for (int i=1;i<=m;i++)
        scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
    sort(edge+1,edge+1+m,cmp);
    for (int i=1;i<=m;)
    {
        mi=ma=-1;
        for (int k=0;k<n;k++)fa[k]=k;
        cnt=0;
        for (j=i;j<=m;j++)
        {
            int s=edge[j].u,t=edge[j].v;
            s=find(s),t=find(t);
            if(s!=t)
            {
                fa[s]=t,cnt++;
                if(cnt==n-1)
                {
                    ma=edge[j].w;
                    break;
                }
            }
        }
        if(ma==-1)break;
        cnt=0;
        for (int k=0;k<n;k++)fa[k]=k;
        for (;j;j--)
        {
            //printf("%d\n",j);
            int s=edge[j].u,t=edge[j].v;
            s=find(s),t=find(t);
            if(s!=t)
            {
                fa[s]=t,cnt++;
                if(cnt==n-1)
                {
                    mi=edge[j].w;
                    i=j+1;
                    break;
                }
            }
        }
        //printf("%d %d\n",mi,ma);
        if(mi==-1)break;
        ans=min(ans,ma-mi);
    }
    cout<<ans<<endl;
    return 0;
}