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
const double inf=9e18;
const double eps=1e-13;
const int N=50005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot,Ans[N];
struct Point{double x,y;};
struct Line{Point A,B;double ang;int id;}a[N],Q[N],Deque[N];
double Cross(Point A,Point B,Point C){
	return (A.x-C.x)*(B.y-C.y)-(A.y-C.y)*(B.x-C.x);
}
bool cmp(Line A,Line B){
	return fabs(A.ang-B.ang)>eps?A.ang<B.ang:Cross(B.A,B.B,A.A)>eps;
}
Point AddCross(Point A,Point B,Point C,Point D){
	Point P;
	double s1=Cross(D,B,A);
	double s2=Cross(C,B,A);
	P.x=(s1*C.x-s2*D.x)/(s1-s2);
	P.y=(s1*C.y-s2*D.y)/(s1-s2);
	return P;
}
bool Check(Line A,Line B,Line C){
	Point P=AddCross(B.A,B.B,C.A,C.B);
	return Cross(A.A,A.B,P)<eps;
}
void Solve(){
	sort(a+1,a+tot+1,cmp);
	Q[++m]=a[1];
	for(int i=2;i<=tot;i++){
		if(a[i].ang-a[i-1].ang>eps)Q[++m]=a[i];
	}
	int l=0,r=1;Deque[0]=Q[1];Deque[1]=Q[2];
	for(int i=3;i<=m;i++){
		while(l<r&&Check(Q[i],Deque[r-1],Deque[r]))r--;
		while(l<r&&Check(Q[i],Deque[l+1],Deque[l]))l++;
		Deque[++r]=Q[i];
	}
	while(l<r&&Check(Deque[l],Deque[r-1],Deque[r]))r--;
	while(l<r&&Check(Deque[r],Deque[l+1],Deque[l]))l++;
	for(int i=l;i<=r;i++)if(Deque[i].id)Ans[++Ans[0]]=Deque[i].id;
}
void AddLine(double A,double B,double C,double D,int id){
	a[++tot].id=id;
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
		double x=read(),y=read();
		AddLine(0,y,1,x+y,i);
	}
	Solve();
	sort(Ans+1,Ans+Ans[0]+1);
	for(int i=1;i<=Ans[0];i++)printf("%d ",Ans[i]);
	return 0;
}