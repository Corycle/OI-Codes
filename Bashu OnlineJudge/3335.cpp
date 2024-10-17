/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const long double inf=1e15;
const long double eps=1e-25;
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot;
struct Point{long double x,y;}P[N];
struct Line{Point A,B;long double ang;int id;}a[N],Q[N],Deque[N];
long double Cross(Point A,Point B,Point C){
	return (A.x-C.x)*(B.y-C.y)-(A.y-C.y)*(B.x-C.x);
}
bool cmp(Line A,Line B){
	return fabs(A.ang-B.ang)>eps?A.ang<B.ang:Cross(B.A,B.B,A.A)>eps;
}
Point Add(Point A,Point B,Point C,Point D){
	long double s1=Cross(D,B,A),s2=Cross(C,B,A);
	return (Point){(s1*C.x-s2*D.x)/(s1-s2),(s1*C.y-s2*D.y)/(s1-s2)};
}
bool Judge(Line A,Line B,Line C){
	Point p=Add(B.A,B.B,C.A,C.B);
	return Cross(A.A,A.B,p)<eps;
}
bool Solve(int mid){
	int num=0;m=0;
	for(int i=1;i<=tot;i++)if(a[i].id<=mid)Q[++m]=a[i];
	for(int i=2;i<=num;i++){
		if(Q[i].ang-Q[i-1].ang>eps)Q[++m]=Q[i];
	}
	int l=1,r=0;
	Deque[++r]=Q[1];Deque[++r]=Q[2];
	for(int i=3;i<=m;i++){
		while(l<r&&Judge(Q[i],Deque[r-1],Deque[r]))r--;
		while(l<r&&Judge(Q[i],Deque[l],Deque[l+1]))l++;
		Deque[++r]=Q[i];
	}
	while(l<r&&Judge(Deque[l],Deque[r-1],Deque[r]))r--;
	while(l<r&&Judge(Deque[r],Deque[l],Deque[l+1]))l++;
	return r-l+1>=3;
}
void AddLine(long double A,long double B,long double C,long double D,int id){
	tot++;
	a[tot].id=id;
	a[tot].A=(Point){A,B};
	a[tot].B=(Point){C,D};
	a[tot].ang=atan2(D-B,C-A);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	AddLine(-inf,-inf,inf,-inf,0);
	AddLine(inf,-inf,inf,inf,0);
	AddLine(inf,inf,-inf,inf,0);
	AddLine(-inf,inf,-inf,-inf,0);
	for(int i=1;i<=n;i++){
		long double X=read(),Y1=read(),Y2=read();
		long double t1=Y1/X,t2=Y2/X;
		AddLine(0,t1,1,t1-X,i);
		AddLine(1,t2-X,0,t2,i);
	}
	sort(a+1,a+tot+1,cmp);
	int l=0,r=n,Ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(Solve(mid)){
			Ans=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	printf("%d",Ans);
	return 0;
}