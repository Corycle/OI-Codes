#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const double Pi=3.14159265358979323846264338327950288419716939937510;
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,a[N],top,L;
struct Point{
	int x,y;
}p[N];
double Sqr(double x){
	return x*x;
}
double Dist(Point A,Point B){
	return sqrt(Sqr(A.x-B.x)+Sqr(A.y-B.y));
}
double Cross(Point A,Point B,Point C){
	return (A.x-C.x)*(B.y-C.y)-(A.y-C.y)*(B.x-C.x);
}
bool cmp(Point x,Point y){
	int v=Cross(x,y,p[1]);
	if(v>0)return 1;
	if(v<0)return 0;
	return Dist(x,p[1])<Dist(y,p[1]);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();L=read();
	double min1=inf,min2=inf;
	int k=0;
	for(int i=1;i<=n;i++){
		p[i].x=read();p[i].y=read();
		if(min2>p[i].y||(min2==p[i].y&&min1>p[i].x)){
			min1=p[i].x;
			min2=p[i].y;
			k=i;
		}
	}
	swap(p[1],p[k]);
	sort(p+2,p+n+1,cmp);
	a[1]=1;a[2]=2;top=2;
	for(int i=3;i<=n;i++){
		while(top>1&&Cross(p[a[top]],p[i],p[a[top-1]])<=0)top--;
		a[++top]=i;
	}
	a[++top]=a[1];
	double ans=2*L*Pi;
	for(int i=2;i<=top;i++){
		ans+=Dist(p[a[i-1]],p[a[i]]);
	}
	printf("%.0lf",ans);
	return 0;
}