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
const double eps=1e-8;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,id,top,a[N];
double Max,Minx,Miny;
struct Point{double x,y;int id;}P[N];
double Sqr(double x){return x*x;}
double Cross(Point A,Point B,Point C){
	return (A.x-C.x)*(B.y-C.y)-(A.y-C.y)*(B.x-C.x);
}
double Dist(Point A,Point B){
	return Sqr(A.x-B.x)+Sqr(A.y-B.y);
}
bool cmp(Point A,Point B){
	double tmp=Cross(A,B,P[1]);
	if(tmp>eps)return true;
	if(tmp<-eps)return false;
	return Dist(A,P[1])<Dist(B,P[1]);
}
void Solve1(){
	Point O=(Point){0,0};
	int id1=0,id2=0;Max=-inf;
	for(int i=1;i<=top;i++)a[i+top]=a[i];
	for(int i=1,j=1;i<=top;i++){
		while(abs(Cross(P[a[i+1]],P[a[j+1]],O))>abs(Cross(P[a[i+1]],P[a[j]],O)))j++;
		if(abs(Cross(P[a[i]],P[a[j]],O))>Max){Max=abs(Cross(P[a[i]],P[a[j]],O));id1=i;id2=j;}
	}
	if(Cross(P[a[id1]],P[a[id2]],O)<eps)swap(id1,id2);
	printf("%d %d\n",P[a[id1]].id,P[a[id2]].id);
}
void Solve2(){
	printf("%d\n",top);
	for(int i=1;i<=top;i++)printf("%d ",P[a[i]].id);
	printf("\n");
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	Minx=Miny=inf;
	for(int i=1;i<=n;i++){
		double m=0,c=0;
		scanf("%lf%lf",&m,&c);
		P[i].x=m*c;P[i].y=m;P[i].id=i;
		if(P[i].y<Miny||(fabs(P[i].y-Miny)<eps&&P[i].x<Minx+eps)){
			Minx=P[i].x;Miny=P[i].y;id=i;
		}
	}
	swap(P[1],P[id]);
	sort(P+2,P+n+1,cmp);
	a[++top]=1;a[++top]=2;
	for(int i=3;i<=n;i++){
		while(top>=2&&Cross(P[i],P[a[top]],P[a[top-1]])>-eps)top--;
		a[++top]=i;
	}
	Solve1();Solve2();
	return 0;
}