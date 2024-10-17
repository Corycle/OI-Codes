#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
struct point{
    long long x,y;
}p[100005];
long long n,b[100005],top;
const long long inf=0x7f7f7f7f7f7f7f7f;
double dis(point p1,point p2)
{
	double x=p1.x-p2.x;
	double y=p1.y-p2.y;
	return sqrt(x*x+y*y);
}
double cross(point p1,point p2,point p0)
{
	double x1=p1.x-p0.x,y1=p1.y-p0.y;
	double x2=p2.x-p0.x,y2=p2.y-p0.y; 
	return x1*y2-x2*y1;
} 
long long cmp(point a,point b)
{
	long long t=cross(a,b,p[1]);
	if(t>0)return 1;
	if(t==0)return dis(a,p[1])<dis(b,p[1]);
	else return 0;
}
void find()
{
    scanf("%lld",&n);
    long long mx=inf,my=inf,k;
	for(long long i=1;i<=n;i++)
	{
	    scanf("%lld%lld",&p[i].x,&p[i].y);
		if(p[i].y<my||(p[i].y==my&&p[i].x<mx))
	        {mx=p[i].x;my=p[i].y;k=i;}	
	}	
	swap(p[1],p[k]);
}
void scan()
{
	b[1]=1;b[2]=2;top=2;
	for(long long i=3;i<=n;i++)
	{
		while(top>1&&cross(p[b[top]],p[i],p[b[top-1]])<=0)top--;
		b[++top]=i;
	}
}
void xzkk(long long m)
{
	long long j=1;
	b[m+1]=b[1];
	double ans=0;
	for(long long i=1;i<=m;i++)
	{
		while(cross(p[b[i+1]],p[b[j+1]],p[b[i]])>cross(p[b[i+1]],p[b[j]],p[b[i]]))j=(j+1)%m;
		ans=max(ans,max(dis(p[b[i]],p[b[j]]),dis(p[b[i+1]],p[b[j+1]])));
	}
    printf("%.2lf",ans);
}
int main()
{
	find();
	sort(p+2,p+n+1,cmp);
	scan();
	//此时b[1~top]为凸包上的点
	xzkk(top);
	return 0;
}