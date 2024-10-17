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
const double eps=1e-8;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int v1,v2,v3;
int Ax,Ay,Bx,By,Cx,Cy,Dx,Dy;
double Sqr(double x){return x*x;}
double Dist(double X1,double Y1,double X2,double Y2){
	return sqrt(Sqr(X1-X2)+Sqr(Y1-Y2));
}
double F(double d,double x,double y){
	double D=Dist(Cx,Cy,Dx,Dy);
	double Ex=Dx-d*((Dx-Cx)/D);
	double Ey=Dy-d*((Dy-Cy)/D);
	return Dist(Ex,Ey,x,y)/v3+Dist(Ex,Ey,Dx,Dy)/v2;
}
double Check(double d){
	double D=Dist(Ax,Ay,Bx,By);
	double Ex=Ax+d*((Bx-Ax)/D);
	double Ey=Ay+d*((By-Ay)/D);
	double l=0,r=Dist(Cx,Cy,Dx,Dy);
	while(r-l>eps){
		double mid1=l+(r-l)/3;
		double mid2=r-(r-l)/3;
		if(F(mid1,Ex,Ey)>F(mid2,Ex,Ey))l=mid1;
		else r=mid2;
	}
	return d/v1+F(l,Ex,Ey);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int flag=0;
	Ax=read();Ay=read();
	Bx=read();By=read();
	Cx=read();Cy=read();
	Dx=read();Dy=read();
	v1=read();v2=read();v3=read();
	if(Ax==Bx&&Ay==By)Ax+=v1,flag=1;
	double l=0,r=Dist(Ax,Ay,Bx,By);
	if(flag==1)l=Dist(Ax,Ay,Bx,By);
	while(r-l>eps){
		double mid1=l+(r-l)/3;
		double mid2=r-(r-l)/3;
		if(Check(mid1)>Check(mid2))l=mid1;
		else r=mid2;
	}
	printf("%.2lf",Check(l)-flag);
	return 0;
}