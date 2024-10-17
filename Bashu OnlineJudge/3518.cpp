#include<bits/stdc++.h>
using namespace std;
long long n,s;
struct _
{
	long long w,c,bian;
	long double bz;
}a[100005];
bool cmp(_ a,_ b)
{
	return a.bz>b.bz;
}
int main()
{
	long long i,j;
	scanf("%lld%lld",&n,&s);
	for(i=1;i<=n;i++)
	{
		scanf("%lld%lld",&a[i].w,&a[i].c);
		a[i].bz=(long double)(a[i].w)/(long double)(a[i].c);
		a[i].bian=i;
	}
	sort(a+1,a+n+1,cmp);
	for(i=1;i<=n;i++)
	{
		if(s>=a[i].c)
		{
			printf("%lld\n",a[i].bian);
			return 0;
		}
	}
	return 0;
}