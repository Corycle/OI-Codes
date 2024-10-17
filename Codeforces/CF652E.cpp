#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define inf 0x3f3f3f3f
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
//struct _{};
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int read(){
    int s=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
    return s*f;
}
int n,m,h[300005],cnt,tot,scc,tp,cntt;
int dfn[300005],low[300005],st[300005],b[300005],sum[300005];
int h2[300005],p[300005][20],dep[300005],dis[300005];
struct edge{
    int to,next,bj;
}d[600005],e[600005];
void hqq_add(int x,int y,int z){
    d[++cnt]=(edge){y,h[x],z};
    h[x]=cnt;
}
void hqq_add2(int x,int y,int z){
    e[++cntt]=(edge){y,h2[x],z};
    h2[x]=cntt;
}
void tarjan(int x,int fa){
    dfn[x]=low[x]=++tot;
    st[++tp]=x;
    for(int i=h[x];i;i=d[i].next){
        int y=d[i].to;
        if(y==fa)continue;
        if(!dfn[y]){
            tarjan(y,x);
            low[x]=min(low[x],low[y]);
        }
        else{
            low[x]=min(low[x],dfn[y]);
        }
    }
    if(dfn[x]==low[x]){
        scc++;
        int k;
        do{
            k=st[tp--];
            b[k]=scc;
        }while(k!=x);
    }
}
void dfs(int x,int depth){
    dep[x]=depth;
    for(int i=h2[x];i;i=e[i].next){
        int y=e[i].to;
        if(dep[y])continue;
        p[y][0]=x;
        dis[y]=dis[x]+sum[y]+e[i].bj;
        dfs(y,depth+1);
    }
}
void ST(){
    int i,j,k=(int)(log(n)/log(2));
    for(j=1;j<=k;j++){
        for(i=1;i<=n;i++){
            if(p[i][j-1]!=-1)p[i][j]=p[p[i][j-1]][j-1];
        }
    }
}
int lca(int x,int y){
    int i,j,k;
    if(dep[x]<dep[y])swap(x,y);
    k=int(log(dep[x])/log(2));
    for(k;k>=0;k--){
        if(dep[x]-(1<<k)>=dep[y])x=p[x][k];
    }
    if(x==y)return x;
    k=int(log(dep[x])/log(2));
    for(k;k>=0;k--){
        if(p[x][k]!=p[y][k]){
            x=p[x][k];
            y=p[y][k];
        }
    }
    return p[x][0];
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
    n=read();m=read();
    for(int i=1;i<=m;i++){
        int x=read(),y=read(),z=read();
        hqq_add(x,y,z);
        hqq_add(y,x,z);
    }
    tarjan(1,0);
//	for(int i=1;i<=n;i++)cout<<b[i]<<endl;
    for(int x=1;x<=n;x++){
        for(int i=h[x];i;i=d[i].next){
            int y=d[i].to;
            if(b[x]==b[y])sum[b[x]]+=d[i].bj;
            else hqq_add2(b[x],b[y],d[i].bj);
        }
    }
    memset(p,-1,sizeof(p));
    dis[1]=sum[1];
    dfs(1,1);
    ST();
    int x,y;
    while(scanf("%d%d",&x,&y)!=EOF){
        x=b[x];y=b[y];
        int z=lca(x,y);
        if(dis[x]+dis[y]-2*dis[z]+sum[z]>0)printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
