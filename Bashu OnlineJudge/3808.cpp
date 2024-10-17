#include<iostream>
#include<iomanip>
#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<stack>
using namespace std;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
double h,t;
struct node{
	double r,x;
}a[10];
struct pp{
	double l,r;
}b[10];
bool yyx(pp x,pp y){
	if(x.l!=y.l)return x.l<y.l;
	return x.r<y.r;
}
double dis(double x,double y){
	return sqrt(x*x-y*y);
}
bool pd(double l){
	int i,j,k;
	for(i=1;i<=7;i++){
		double len=dis(a[i].r+l,h);
		b[i].l=a[i].x-len;
		b[i].r=a[i].x+len;
	}
	sort(b+1,b+8,yyx);
	double s=0;
	for(i=1;i<=7;i++){
		if(b[i].l>s)return false;
		s=max(s,b[i].r);
		if(s>t)return true;
	}
	if(s<t)return false;
	return true;
}
double dist(double x,double y){
	return sqrt(x*x+y*y);
}
int main(){
//	freopen("rainbow.in","r",stdin);
//	freopen("rainbow.out","w",stdout);
	int i,j,k;
	scanf("%lf%lf",&h,&t);
	double l=0,r=0;
	for(i=1;i<=7;i++){
		scanf("%lf%lf",&a[i].x,&a[i].r);
		r=max(r,h-a[i].r);
		r=max(r,dist(a[i].x,h)-a[i].r);
		r=max(r,dist(t-a[i].x,h)-a[i].r);
	}
//	cout<<r<<endl;
	while(l<=r){
		if(r-l<=0.0001)break;
		double mid=(l+r)/2;
		if(pd(mid))r=mid;
		else l=mid;
	}
	printf("%.2lf",l);
	return 0;
}
/*
87.20 2955.25
9306.25 379.83
1587.65 881.07
653.83 939.21
3384.39 818.71
8069.61 30.49
306.37 300.35
7695.43 646.25
*/