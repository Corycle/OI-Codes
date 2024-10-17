#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<queue>
using namespace std;
priority_queue<int> q;
struct haha
{
	int c,t;
}a[100005];
bool cmp(haha d,haha b)
{
	return d.c<b.c;
}
int sum;
int main()
{
	int i,n;
	scanf("%d",&n);
	for(i=1;i<=n;i++)scanf("%d%d",&a[i].t,&a[i].c);
	sort(a+1,a+n+1,cmp);
	for(i=1;i<=n;i++)
	{
		q.push(a[i].t);
		sum+=a[i].t;
		if(sum>a[i].c)
		{
			sum-=q.top();
			q.pop();
		}
	}
	printf("%d",q.size());
	return 0;
}