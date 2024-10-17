#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<queue>
#define pa pair<int,int>
#define mk make_pair
using namespace std;
int num,head[10010*11],n,m,k,S,T;
struct node{
    int to,pre,v;
}e[50010*11*2];
void Insert(int from,int to,int v){
    for(int i=head[from];i;i=e[i].pre)
        if(e[i].to==to){
            e[i].v=min(e[i].v,v);
            return;
        }
    e[++num].to=to;
    e[num].v=v;
    e[num].pre=head[from];
    head[from]=num;
}
int Cal(int x,int y){
    return x*11+y;
}
priority_queue<pa,vector<pa>,greater<pa> >q;
bool vis[50010*11];
int dis[50010*11];
void Dij(int s){
    q.push(mk(0,s));
    memset(dis,127/3,sizeof(dis));
    dis[s]=0;
    while(!q.empty()){
        int now=q.top().second;q.pop();
        if(vis[now])continue;
        vis[now]=1;
        for(int i=head[now];i;i=e[i].pre){
            int to=e[i].to;
            if(dis[to]>e[i].v+dis[now]){
                dis[to]=e[i].v+dis[now];
                q.push(mk(dis[to],to));
            }
        }
    }
}
int main(){
    scanf("%d%d%d%d%d",&n,&m,&k,&S,&T);
    S++;T++;
    int x,y,z;
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&x,&y,&z);
        x++,y++;
        for(int j=0;j<=k;j++){
            int x1=Cal(x,j),y1=Cal(y,j);
            Insert(x1,y1,z);
            Insert(y1,x1,z);
            if(j){
                int x2=Cal(x,j-1),y2=Cal(y,j-1);
                Insert(x1,y2,0);
                Insert(y1,x2,0);
            }
        }
    }
    Dij(Cal(S,k));
    int ans=0x7fffffff;
    for(int i=0;i<=k;i++)
        ans=min(ans,dis[Cal(T,i)]);
    printf("%d",ans);
}