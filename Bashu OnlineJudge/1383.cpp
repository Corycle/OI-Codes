#include<cstdio>
#include<cstring>
using namespace std;
const int m1=10005,inf=0x7fffffff,m2=20005;
struct Edge
{
	int to,v,next;
}w[m2];
int h[m1],d[m1],q[m2],s[m1],used[m1],sx,fx;
int n,m,cnt;
int t[8]={0,2,6,4,8,6,10,14};
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
	for(int i=1;i<=7;i++){
		scanf("%d",&x);
		if(x)t[i]/=2;
	}
	scanf("%d%d",&sx,&fx);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		AddEdge(x,y,t[z]);
		AddEdge(y,x,t[z]);
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
	if(d[fx]!=inf)printf("%d",d[fx]);
	return 0;
} 