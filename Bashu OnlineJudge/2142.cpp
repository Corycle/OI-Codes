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
const int N=10005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,top,a[N];
struct Point{
	double x,y;
}p[N];
double Cross(Point A,Point B,Point C){
	return (A.x-C.x)*(B.y-C.y)-(A.y-C.y)*(B.x-C.x);
}
double Dist(Point A,Point B){
	return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}
bool cmp(Point A,Point B){
	double v=Cross(A,B,p[1]);
	if(v>0)return 1;
	if(v<0)return 0;
	return Dist(A,p[1])<Dist(B,p[1]);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	int k=0;
	double min1=inf,min2=inf;
	for(int i=1;i<=n;i++){
		scanf("%lf%lf",&p[i].x,&p[i].y);
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
		while(top>1&&Cross(p[i],p[a[top]],p[a[top-1]])>0)top--;
		a[++top]=i;
	}
	a[++top]=a[1];
	double ans=0;
	for(int i=2;i<=top;i++){
		ans+=Dist(p[a[i-1]],p[a[i]]);
	}
	printf("%.2lf",ans);
	return 0;
}
