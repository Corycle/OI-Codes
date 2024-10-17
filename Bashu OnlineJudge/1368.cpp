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
const double eps=1e-10;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
double X,Y,L,D;
double Sqr(double x){
	return x*x;
}
double F(double Sin){
	double Cos=sqrt(Sqr(1)-Sqr(Sin));
	double Tan=Sin/Cos;
	double A=X/Tan+Y;
	double B=A-D/Sin;
	return B/Cos;
}
double Solve(double l,double r){
	while(r-l>eps){
		double mid1=l+(r-l)/3;
		double mid2=r-(r-l)/3;
		if(F(mid1)>F(mid2))l=mid1;
		else r=mid2;
	}
	return l;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	while(scanf("%lf%lf%lf%lf",&X,&Y,&L,&D)!=EOF){
		double ans=Solve(0,1);//Sin
		if(F(ans)>=L)printf("yes\n");
		else printf("no\n");
	}
	return 0;
}