#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long n,minn=0x7fffffffffffffff,minnl,x;
struct _
{
	long long number,sum;
}q[100005];
bool jsb(_ a,_ b)
{
	return a.sum<b.sum;
}
int main()
{
	int i;
	scanf("%d",&n); 
	for(i=1;i<=n;i++){scanf("%lld",&x);q[i].sum=q[i-1].sum+x;q[i].number=i;}
	sort(q,q+n+1,jsb);
	for(i=1;i<n;i++)
	{
		if(abs(q[i+1].sum-q[i].sum)<minn)
		{
			minn=abs(q[i+1].sum-q[i].sum);
			minnl=abs(q[i+1].number-q[i].number);
		}
		else if(abs(q[i+1].sum-q[i].sum)==minn)
		{
			minnl=max(abs(q[i+1].number-q[i].number),minnl);
		}
	}
	printf("%lld\n%lld\n",minn,minnl);
	return 0;
}