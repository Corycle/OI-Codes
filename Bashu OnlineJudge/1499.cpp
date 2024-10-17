#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cmath>
using namespace std;
int n,k;
struct Tree
{
	int w,d;
}p[50005];
bool cmp(Tree pp,Tree ppp)
{
	if(pp.w==ppp.w)
	return pp.d<ppp.d;
	return pp.w>ppp.w;
}

int e[50005],c[15];
int main()
{
	scanf("%d %d",&n,&k);
	for(int i=1;i<=10;i++)
	scanf("%d",&e[i]);
	for(int i=1;i<=n;i++)
	{
	scanf("%d",&p[i].w);
	p[i].d=i;
    }	
	sort(p+1,p+1+n,cmp);
	
	for(int i=1;i<=n;i++)
	{
		p[i].w+=e[(i-1)%10+1];
	}
	sort(p+1,p+1+n,cmp);
	for(int i=1;i<=k;i++)
	{
		printf("%d ",p[i].d);
	}
	printf("\n");
	return 0;
}