#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

struct edge
{
    int x,y,v;
}cr[100050];
bool cmp(edge a,edge b) {return a.v>b.v;}
int n,m;
int an[20050],pr[20050],en[20050];

int get_father(int x)
{
    if(pr[x]==x) return x;
    pr[x]=get_father(pr[x]);
    return pr[x];
}
void Union(int x,int y)
{
    int fx=get_father(x);
    int fy=get_father(y);
    if(fx!=fy) pr[fx]=fy;
}

int main()
{
    scanf("%d%d",&n,&m);
    int x,y,v;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&cr[i].x,&cr[i].y,&cr[i].v);
    }
    sort(cr+1,cr+m+1,cmp);
    memset(pr,0,sizeof(pr));
    memset(en,0,sizeof(en));
    for(int i=1;i<=n;i++) {pr[i]=i;en[i]=0;}
    for(int i=1;i<=m;i++)
    {
        x=cr[i].x;
        y=cr[i].y;
        int fx=get_father(x);
        int fy=get_father(y);
        if(fx==fy)
        {
            printf("%d\n",cr[i].v);
            return 0;
        }
        if(en[x]==0) en[x]=y;
        else Union(y,en[x]);
        if(en[y]==0) en[y]=x;
        else Union(x,en[y]);
    }
    printf("0\n");
    return 0;
}
/*

这道题首先要想到并查集思路,这是解题的基础。
首先考虑问题，如何安排罪犯才能做到最优决策？
明显的可以看出，要尽量先安排仇恨值大的组合，
将他们放到不同的监狱里。
从大到小进行决策直到发现有某一组组合已经在同一个监狱里，
那么输出他们的仇恨值就是最终的答案。现在问题又来了，
第一组罪犯可以轻松地随意安排到两个监狱中，
但是从第二组开始，两个人到底应该各自去哪一个监狱呢？
这时要改变思路
既然维护罪犯在哪一个监狱不方便
那么我们干脆维护某两个罪犯不在一个监狱好了
考虑到并查集的本职工作是维护某两点在一个集合
不能很好地处理不在一个集合的情况，所以我们要曲线救国
通过保存某个点的“敌人”集合来代表和他不在一个监狱的罪犯
间接地实现维护某两点不在一个集合的情况。在加入关系的时候进行判断
如果某两点已经在一个集合
说明他们无论如何也安排不到不同的两个监狱了，输出仇恨值即可。

至此算法框架基本浮现。
（P.s 用并查集保存两点不在一个集合还可以使用对立点的方式
即给每一个实点都建立一个与之对立的虚点
当读取到A与B不在同一集合的信息时
将A与B'，B与A'分别连边
这样也可以表示A与B不在同一集合。
断过程与上面的方法相同
实现起来也很简单
大家不妨试一下）


*/