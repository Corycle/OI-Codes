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
#define double long double
using namespace std;
const int inf=0x3f3f3f3f;
const double eps=1e-16;
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot;
struct Point{double x,y;}P[N],O;
struct Line{Point A,B;double ang;}L[N],Deque[N];
double Cross(Point A,Point B,Point C){
	return (A.x-C.x)*(B.y-C.y)-(A.y-C.y)*(B.x-C.x);
}
bool cmp(Line A,Line B){
	return fabs(A.ang-B.ang)>eps?A.ang<B.ang:Cross(B.A,B.B,A.A)>eps;
}
void AddLine(double A,double B,double C,double D){
	tot++;
	L[tot].A=(Point){A,B};
	L[tot].B=(Point){C,D};
	L[tot].ang=atan2(D-B,C-A);
}
Point AddPoint(Point A,Point B,Point C,Point D){
	double s1=Cross(D,B,A),s2=Cross(C,B,A);
	return (Point){(s1*C.x-s2*D.x)/(s1-s2),(s1*C.y-s2*D.y)/(s1-s2)};
}
Point AddPoint(Line A,Line B){return AddPoint(A.A,A.B,B.A,B.B);}
bool Judge(Line A,Line B,Line C){
	Point p=AddPoint(B.A,B.B,C.A,C.B);
	return Cross(A.A,A.B,p)<eps;
}
double Calc(){
	P[n+1]=P[1];
	double ans=0;
	for(int i=1;i<=n;i++)ans+=Cross(P[i],P[i+1],O);
	return fabs(ans);
}
double Solve(){
	m=1;
	sort(L+1,L+tot+1,cmp);
	for(int i=2;i<=tot;i++){
		if(L[i].ang-L[i-1].ang>eps)L[++m]=L[i];
	}
	int l=1,r=0;
	Deque[++r]=L[1];Deque[++r]=L[2];
	for(int i=3;i<=m;i++){
		while(l<r&&Judge(L[i],Deque[r-1],Deque[r]))r--;
		while(l<r&&Judge(L[i],Deque[l],Deque[l+1]))l++;
		Deque[++r]=L[i];
	}
	while(l<r&&Judge(Deque[l],Deque[r-1],Deque[r]))r--;
	while(l<r&&Judge(Deque[r],Deque[l],Deque[l+1]))l++;
	n=0;
	Deque[r+1]=Deque[l];
	for(int i=l;i<=r;i++)P[++n]=AddPoint(Deque[i],Deque[i+1]);
	return Calc();
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=0;i<n;i++){P[i].x=read();P[i].y=read();}P[n]=P[0];
	for(int i=0;i<n;i++)AddLine(P[i].x,P[i].y,P[i+1].x,P[i+1].y);
	for(int i=1;i<n;i++){
		double A=P[0].y-P[1].y-P[i].y+P[i+1].y;
		double B=P[1].x-P[0].x-P[i+1].x+P[i].x;
		double C=Cross(P[0],P[1],O)-Cross(P[i],P[i+1],O);
		if(fabs(A)>eps)AddLine(-C/A,0,-B-C/A,A);
		else AddLine(0,-C/B,-B,A-C/B);
	}
	double S1=Calc();
	double S2=Solve();
	printf("%.4LF",S2/S1);
	return 0;
}