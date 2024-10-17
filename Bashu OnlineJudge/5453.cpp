#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const double eps=1e-15;
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,tot,cnt;
struct Point{double x,y;}a[N];
struct Line{Point a,b;double tag;}q[N],Deque[N];
double Cross(Point A,Point B,Point C){
	return (A.x-C.x)*(B.y-C.y)-(A.y-C.y)*(B.x-C.x);
}
Point Add(Point A,Point B,Point C,Point D){
	double s1,s2;
	s1=Cross(D,B,A);
	s2=Cross(C,B,A);
	Point p;
	p.x=(s1*C.x-s2*D.x)/(s1-s2);
	p.y=(s1*C.y-s2*D.y)/(s1-s2);
	return p;
}
bool cmp(Line x,Line y){
	if(fabs(x.tag-y.tag)<=eps)return Cross(y.a,y.b,x.a)>eps;
	return x.tag<y.tag;
}
bool pd(Line l0,Line l1,Line l2){
	Point p=Add(l1.a,l1.b,l2.a,l2.b);
	return Cross(l0.a,l0.b,p)<-eps;
}
void AddLine(double A,double B,double C,double D){
	tot++;
	q[tot].a.x=A;q[tot].a.y=B;
	q[tot].b.x=C;q[tot].b.y=D;
	q[tot].tag=atan2(D-B,C-A);
}
int Solve(int x){
	memset(q,0,sizeof(q));
	memset(Deque,0,sizeof(Deque));
	tot=0;
	for(int i=1;i<=n;i++){
		AddLine(a[i].x,a[i].y,a[i+x+1].x,a[i+x+1].y);
	}	
	int i,j;
	sort(q+1,q+tot+1,cmp);
	j=1;
	for(i=2;i<=tot;i++){
		if(q[i].tag-q[i-1].tag>eps)q[++j]=q[i];
	}//去掉平行的直线
	tot=j;
	int l=0,r=1;
	Deque[0]=q[1];
	Deque[1]=q[2];
	for(i=3;i<=tot;i++){//更新当前凸包,删除无用边
		while(l<r&&pd(q[i],Deque[r-1],Deque[r]))r--;
		while(l<r&&pd(q[i],Deque[l+1],Deque[l]))l++;
		Deque[++r]=q[i];
	}
	while(l<r&&pd(Deque[l],Deque[r-1],Deque[r]))r--;
	while(l<r&&pd(Deque[r],Deque[l+1],Deque[l]))l++;
	if(r<=l+1)return 0;
	return 1;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=n;i>=1;i--){
		a[i].x=a[i+n].x=read();
		a[i].y=a[i+n].y=read();
	}
	int l=0,r=n,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(Solve(mid)){
			ans=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	printf("%d",ans);
	return 0;
}