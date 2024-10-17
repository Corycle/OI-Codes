#include<cstdio>
#define maxn 110
#define max(a,b)    a>b?a:b
using namespace std;
int map[maxn][maxn],f[maxn][maxn],r,c,dfs(int,int),m;
/*
map存跑道，f存答案，
r，c为纵坐标横坐标，
dfs搜索函数，两个变量分别为被搜索点的纵、横坐标。
底下函数x，y打反了， 即x代表纵坐标，x代表横坐标，别看晕了
m为最长跑道长度，全局变量初始值为0。 
*/ 
int main(){
    scanf("%d%d",&r,&c);
    for(int i=1;i<=r;i++)
        for(int j=1;j<=c;j++){
            scanf("%d",&map[i][j]);f[i][j]=1;
/*
    输入，因为自己滑到自己的长度是1，所以答案数组初始化为1。 
*/
        }           
    for(int i=1;i<=r;i++)
        for(int j=1;j<=c;j++)
            m=max(m,dfs(i,j));      //进行搜索，如果结果比已知答案更大就更新。 
    printf("%d",m);                   //输出答案 
    return 0;
}
inline int dfs(int x,int y){        //搜索函数，其中x代表纵坐标，y代表横坐标，一开始打反了，后面懒得改了，别看晕了 
    if(f[x][y]!=1)  return f[x][y];
    int b=0;
/*
    以下四句if，每个括号中前四句条件是否到达边界，最后一条件判断是否当前坐标比搜索坐标高。 
*/ 
    if(x>=1&&y>=1&&x<r&&y<=c&&map[x][y]>map[x+1][y]) b=max(b,(dfs(x+1,y)+1));
    if(x>=1&&y>=1&&x<=r&&y<c&&map[x][y]>map[x][y+1]) b=max(b,(dfs(x,y+1)+1));
    if(x>1&&y>=1&&x<=r&&y<=c&&map[x][y]>map[x-1][y]) b=max(b,(dfs(x-1,y)+1));
    if(x>=1&&y>1&&x<=r&&y<=c&&map[x][y]>map[x][y-1]) b=max(b,(dfs(x,y-1)+1));
    f[x][y]=max(f[x][y],b); //防止4个if都不成立即b为0的情况。故取最大值 
    return f[x][y];
}