#include<iostream>
#include<iomanip>
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
struct que
{
	int a[4][4];
	int d;
};
int mu[4][4],qi[4][4],dx[4]={1,0,-1,0},dy[4]={0,1,0,-1};
int f[10]={1,1,2,6,24,120,720,5040,40320,326880};
bool h[10000005];
int ans[10000005];
int key1,key2;
queue<que> q;
void init()
{
	qi[1][2]=1; qi[1][3]=2; qi[2][1]=3;
	qi[2][2]=4; qi[2][3]=5; qi[3][1]=6;
	qi[3][2]=7; qi[3][3]=8;
}
int key(int a[][4])
{
	int ans=0;
	for(int i=3;i<=11;i++)
	{
		int tmp=0;
		for(int j=i+1;j<=11;j++)
		{
			if(a[i/3][i%3+1]>a[j/3][j%3+1]) tmp++;
		}
		ans+=tmp*f[11-i];
	}
	return ans;
}
bool hash(int a[][4])
{
	key1=key(a);
	if(h[key1]) return false;
	else return true;
}
bool bfs()
{
	que r;
	memcpy(r.a,qi,sizeof(qi));
	r.d=0;
	q.push(r);
	key1=key(qi);
	h[key1]=true;
	ans[key1]=0;
	while(!q.empty())
	{
		que u=q.front();
	/*	for(int i=1;i<=3;i++)
		{
			for(int j=1;j<=3;j++)
			{
				printf("%d ",u.a[i][j]);
			}
			printf("\n");
		}
		getchar();*/
		q.pop();
		swap(u.a[2][1],u.a[2][3]);
		swap(u.a[2][1],u.a[2][2]);
		if(hash(u.a))
		{
			memcpy(r.a,u.a,sizeof(u.a));
			r.d=u.d+1;
			h[key1]=true;
			ans[key1]=u.d+1;
			q.push(r);
		}
		swap(u.a[2][1],u.a[2][2]);
		swap(u.a[2][1],u.a[2][3]);
		swap(u.a[1][1],u.a[2][1]);
		swap(u.a[1][1],u.a[3][1]);
		swap(u.a[1][1],u.a[3][2]);
		swap(u.a[1][1],u.a[3][3]);
		swap(u.a[1][1],u.a[2][3]);
		swap(u.a[1][1],u.a[1][3]);
		swap(u.a[1][1],u.a[1][2]);
		if(hash(u.a))
		{
			h[key1]=true;
			ans[key1]=u.d+1;
			memcpy(r.a,u.a,sizeof(u.a));
			r.d=u.d+1;
			q.push(r);
		}
	}
}
int main()
{
	memset(ans,-1,sizeof(ans));
	init();
	bfs();
	while(~scanf("%d",&mu[1][1]))
	{
		for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
		{
			if(i==1&&j==1) continue;
			scanf("%d",&mu[i][j]);
		}
		key1=key(mu);
		if(ans[key1]>=0) printf("%d\n",ans[key1]);
		else printf("UNSOLVABLE\n");
	}
}