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
const int N=2005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,top,a[N*2];
struct Point{
	double x,y;
}p[N];
double ans;
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
	n=read();
	double min1=inf,min2=inf;
	int k=0;
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
		while(top>1&&Cross(p[a[top]],p[i],p[a[top-1]])<=0)top--;
		a[++top]=i;
	}
	for(int i=1;i<=top;i++)a[top+i]=a[i];
	int n1=0,n2=0,n3=0,n4=0;
	for(int k=1;k<=top;k++){
		n1=k;n2=k+1;n4=k+3;
		for(int i=k+2;i<=top;i++){
			n3=i;
			double s1=abs(Cross(p[a[n2]],p[a[n3]],p[a[n1]]));
			double s2=abs(Cross(p[a[n3]],p[a[n4]],p[a[n1]]));
			while(n2+1<n3){
				double S=Cross(p[a[n2+1]],p[a[n3]],p[a[n1]]);
				if(S>s1){
					s1=S;
					n2++;
				}
				else break;
			}
			while(n4+1<n1+top){
				double S=Cross(p[a[n3]],p[a[n4+1]],p[a[n1]]);
				if(S>s2){
					s2=S;
					n4++;
				}
				else break;
			}
			ans=max(ans,s1+s2);
		}
	}
	printf("%.3lf",ans/2);
	return 0;
}