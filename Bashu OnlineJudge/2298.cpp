#include<cstdio>
#include<cstring>
using namespace std;
const int m1=100005,inf=0x7fffffff,m2=1000005;
struct Edge
{
	int to,v,next;
}w[m2];
int h[m1],d[m1],q[m2],s[m1],used[m1],sx,fx;
int n,m,cnt;
void AddEdge(int x,int y,int z)//邻接表 
{
	cnt++;//边数++ 
	w[cnt].to=y;//这条边的目的地 
	w[cnt].v=z;//这条边的权值 
	w[cnt].next=h[x];//h[x]存的x上一条边的编号 
	h[x]=cnt;//让下一条x的边存入，最后方便找回去 
}
void read()
{
	int x,y,z;
	scanf("%d%d",&n,&m);
	sx=1;fx=n;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		AddEdge(x,y,1);
	}
}
void SPFA()
{
	int H=1,t=1,i,j,p;
	for(i=1;i<=n;i++)d[i]=inf;//求最小，变为最大 
	d[sx]=0;//到当前点当然为0
	q[1]=sx;//队列 
	s[sx]=1;//判断是否入队的数组 
	while(H<=t)//队列不为空 
	{
		i=q[H];//新节点 
		s[i]=0;//标记 
		for(p=h[i];p!=0;p=w[p].next)//从第一条开始，用邻接表，找回去
		{
			j=w[p].to;//当前边的目的地 
			if(d[j]>d[i]+w[p].v)//更新到目的地的最短路径 
			{
				d[j]=d[i]+w[p].v;
				if(!s[j])//存在更短就入队，继续造更短 
				{
					t++;
					q[t]=j;//顶点入队 
					s[j]=1;//标记已用 
				}
			}
		}
		H++;//出队 
	}
}
int main()
{
	read();
	SPFA();
	if(d[fx]!=inf)printf("%d",d[fx]+1);
	else printf("No Solution");
	return 0;
} 