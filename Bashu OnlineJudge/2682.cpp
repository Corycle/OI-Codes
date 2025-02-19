#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>
#include<algorithm>
#define E 0x3f3f3f3f
#define MAXN 5010  
#define MAXM 100100 
using namespace std;
int n,m;

struct node{
    int u,v,next,w;
}e[MAXM*2];
int head[MAXN];
int cnt;
bool r[MAXN];
int dis[MAXN];
int dis2[MAXN];
void add(int u,int v,int w){
    cnt++;
    e[cnt].u = u;
    e[cnt].v = v;
    e[cnt].w = w;
    e[cnt].next = head[u];
    head[u] = cnt;
}

void SPFA(int orz,int d[]){//裸的SPFA 
    memset(r,0,sizeof r);
    queue<int>q;
    d[orz] = 0;
    q.push(orz);
    r[orz] = true;
    while(!q.empty()){
        int h=q.front();
        q.pop();
        r[h] = 0;
        for(int i=head[h];i!=0;i=e[i].next){
            if(e[i].w+d[e[i].u]<d[e[i].v]){
                d[e[i].v]=e[i].w+d[e[i].u];
                if(r[e[i].v]==0){
                    q.push(e[i].v);
                    r[e[i].v]=1;
                }
            }
        }
    }
}

int main(){
    while(~(scanf("%d%d",&n,&m))){
    cnt = 0;
    memset(dis,E,sizeof dis);
    memset(dis2,E,sizeof dis2);
    memset(head,0,sizeof head);
        for(int i=1;i<=m;++i){
            int a,b,c;
            scanf("%d%d%d",&a,&b,&c);
            add(a,b,c);
            add(b,a,c);
        }
        SPFA(1,dis);//求出1到所有点的最短距离
        SPFA(n,dis2);//求出n到所有点的最短距离 
        int minn = dis[n];//次短路当然大于最短路啦
        int ans = E;//先把答案置为最大值，以便于更新
        for(int i=1;i<=n;++i){//枚举每一个点 
            for(int j=head[i];j;j=e[j].next){//每个点的连点
                int v=e[j].v;//终点 
                int w=e[j].w;//权值 
                if(dis[i] + dis2[v] + w >minn && dis[i] + dis2[v] + w < ans){
                    ans = dis[i]+dis2[v]+w;
                }/*如果说1到i这个点的距离加上其的终边到n的距离并加上其终边的权值大于了最短路，并且他小于当前的次短路，那么更新答案*/ 
            }
        }//其实就是一个暴力更新 
        printf("%d\n",ans);//输出走人
    }
    return 0;
}