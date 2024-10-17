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
//struct _{};
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
const int ed[6][6]={
    {0,0,0,0,0,0},
    {0,1,1,1,1,1},
    {0,0,1,1,1,1},
    {0,0,0,2,1,1},
    {0,0,0,0,0,1},
    {0,0,0,0,0,0}
};
int dx[8]={1,1,-1,-1,2,2,-2,-2};
int dy[8]={2,-2,2,-2,1,-1,1,-1};
int v[6][6],ans;
bool A_star(int s)
{
    int k=0;
    for(int i=1;i<=5;i++)
    {
        for(int j=1;j<=5;j++)
        {
            if(v[i][j]!=ed[i][j])
            {
                k++;
                if(k+s>ans)return 0;
            }
        }
    }
    return 1;
}
bool ok()
{
    for(int i=1;i<=5;i++)
    {
        for(int j=1;j<=5;j++)
        {
            if(v[i][j]!=ed[i][j])return 0;
        }
    }
    return 1;
}
bool bk;
void dfs(int x,int y,int s)
{
    if(s>ans)return;
    if(ok())
    {
        if(s==ans)bk=false;
        return;
    }
    for(int i=0;i<8;i++)
    {
        int nx=x+dx[i],ny=y+dy[i];
        if(nx<=5&&nx>0&&ny<=5&&ny>0)
        {
            swap(v[x][y],v[nx][ny]);
            if(A_star(s))dfs(nx,ny,s+1);
            swap(v[x][y],v[nx][ny]);
        }
    }
}
char ss[10];
int main()
{
    int T;scanf("%d",&T);
    while(T--)
    {
        int sx,sy;
        for(int i=1;i<=5;i++)
        {
            scanf("%s",ss+1);
            for(int j=1;j<=5;j++)
            {
                if(ss[j]=='*')v[i][j]=2,sx=i,sy=j;
                else v[i][j]=ss[j]-'0';
            }
        }
        bk=true;
        for(ans=0;ans<=15;ans++)
        {
            dfs(sx,sy,0);
            if(!bk){printf("%d\n",ans);break;}
        }
        if(bk)printf("-1\n");
    }
    return 0; 
}