#include<iostream>
#include<iomanip>
#include<cstring>
#include<queue>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
using namespace std;
int du[10005],f[10005],chu[10005][2005],num[10005];
long long sum=0;
queue<int>q;
int main()
{
	int n,m,p=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		du[x]++;//x的度++ 
		num[y]++;//比y高的人数++ 
		chu[y][num[y]]=x;//y比第几个低 
	}
	for(int i=1;i<=n;i++)
	{
		if(du[i]==0)//不比任何人高 
		{
			q.push(i);//入队 
			f[i]=100;//最少的 
		}
	}
	while(!q.empty())//队列不为空 
	{
		int u=q.front();//头 
		q.pop();//出队 
		p++;//
		for(int i=1;i<=num[u];i++)//边的种数 
		{
			f[chu[u][i]]=f[u]+1;//应该多1块钱 
			du[chu[u][i]]--;//入度--，比他多的人-- 
			if(du[chu[u][i]]==0)//度为0，入队 
			{
			    q.push(chu[u][i]);
			}
		}
	}
	for(int i=1;i<=n;i++)sum+=f[i];//总和 
	if(p==n)cout<<sum;//找了n个 
	else cout<<"Poor Xed";
	return 0; 
}