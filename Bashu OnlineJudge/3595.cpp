#include<bits/stdc++.h>
using namespace std;
int sum,ans1,ans2,n,m,a[505][505],vis[505][505],flag[505][505],rd[505*505],cd[505*505];
//flag[i][j]代表(i,j)属于哪一个块   sum为块的编号 
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
struct _
{
	int x,y;
}q[505*505];
void read()
{
	int i,j;
	scanf("%d%d",&m,&n);
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)scanf("%d",&a[i][j]);
	}
}
void BFS(int sx,int sy)//广搜 搜出每一个块的元素 
{
	int h=1,t=1,nx,ny,i;
	q[1].x=sx;q[1].y=sy;vis[sx][sy]=1;
	flag[sx][sy]=sum;
	while(h<=t)
	{
		int x=q[h].x;
		int y=q[h].y;
		for(i=0;i<=3;i++)
		{
			nx=x+dx[i];ny=y+dy[i];
			if(a[x][y]==a[nx][ny]&&nx>=1&&nx<=n&&ny>=1&&ny<=m&&!vis[nx][ny])
			{//同一高度且没搜过 
				vis[nx][ny]=1;
				t++;
				q[t].x=nx;
				q[t].y=ny;
				flag[nx][ny]=sum;//标记 
			}
		}
		h++;
	}
}
void solve()
{
	int i,j,k;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			if(!vis[i][j])//没有搜过就搜 
			{
				sum++;
				BFS(i,j);
			}
		}
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			for(k=0;k<=3;k++)
			{
				int nx=i+dx[k];
				int ny=j+dy[k];
				if(flag[nx][ny]!=flag[i][j])
				{//计算两个不同块的出度以及入度  
				// 高的向低的位置运动 
					if(a[i][j]>=a[nx][ny]&&nx>=1&&nx<=n&&ny>=1&&ny<=m)
					{
						cd[flag[i][j]]++;
						rd[flag[nx][ny]]++;
					}
					else if(a[i][j]<=a[nx][ny]&&nx>=1&&nx<=n&&ny>=1&&ny<=m)
					{
						rd[flag[i][j]]++;
						cd[flag[nx][ny]]++;
					}
				}
				
			}
		}
	}
}
int main()
{
	read();
	solve();
	for(int i=1;i<=sum;i++)
	{
		if(!cd[i])ans1++;
		if(!rd[i])ans2++;
	}
	if(sum!=1)printf("%d\n",max(ans1,ans2));//取最大值 
	else printf("0\n");//特殊情况，图中只有一个块，故不需要缆车 
	return 0;
}