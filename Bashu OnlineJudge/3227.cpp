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
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
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
double ans1=inf,ans2;
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
void Ask(int m){
	int j=1;
	a[m+1]=a[1];
	for(int i=1;i<=m;i++){
		while(Cross(p[a[i+1]],p[a[j+1]],p[a[i]])>Cross(p[a[i+1]],p[a[j]],p[a[i]]))j=(j+1)%m;
		ans2=max(ans2,max(Dist(p[a[i]],p[a[j]]),Dist(p[a[i+1]],p[a[j+1]])));
	}
}
bool cmp1(Point A,Point B){
	if(A.x!=B.x)return A.x<B.x;
	return A.y<B.y;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	ll k=0,min1=inf,min2=inf;
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
		while(top>1&&Cross(p[i],p[a[top]],p[a[top-1]])>=0)top--;
		a[++top]=i;
	}
	Ask(top);
	sort(p+1,p+n+1,cmp1);
	for(int i=1;i<=n;i+=10){
		int l=i,r=min(i+20,n);
		for(int j=l;j<=r;j++){
			for(k=j+1;k<=r;k++){
				ans1=min(ans1,Dist(p[j],p[k]));
			}
		}
	}
	printf("%.2lf %.2lf",ans1,ans2);
	return 0;
}