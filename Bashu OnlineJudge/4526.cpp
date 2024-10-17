#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
const int N=100005;
int n,pos,ans,lst;
bool vis[N];
struct node
{
	int dis,tir,num;
}a[N];
struct cmp1
{
	bool operator()(node c,node d)
	{
		return c.tir<d.tir;
	}
};
struct cmp2
{
	bool operator()(node c,node d)
	{
		return c.tir+2*c.dis<d.tir+2*d.dis;
	}
};
priority_queue<node,vector<node>,cmp1>q1;
priority_queue<node,vector<node>,cmp2>q2;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i].dis);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i].tir);
	for(int i=1;i<=n;i++)
		a[i].num=i;
	for(int i=1;i<=n;i++)
		q2.push(a[i]);
	for(int i=1;i<=n;i++)
	{
		int val1,val2;
		while(!q1.empty()&&vis[q1.top().num])
			q1.pop();
		if(q1.empty())
			val1=0;
		else
			val1=q1.top().tir;
		while(!q2.empty()&&q2.top().num<=lst)
			q2.pop();
		if(q2.empty())
			val2=0;
		else
			val2=q2.top().tir+2*(q2.top().dis-pos);
		if(val1>=val2)
		{
			ans+=val1;
			vis[q1.top().num]=1;
			q1.pop();
		}
		else
		{
			ans+=val2;
			vis[q2.top().num]=1;
			for(int i=lst+1;i<=q2.top().num;i++)
				q1.push(a[i]);
			lst=q2.top().num;
			pos=a[lst].dis;
			q2.pop();
		}
		printf("%d\n",ans);
	}
	return 0;
}
