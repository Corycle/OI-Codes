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
const int inf=0x3f3f3f3f;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
double a,b,c,d;
double F(double x){
	return (c*x+d)/(a*x+b);
}
double Simpson(double L,double R){
	double mid=(L+R)/2;
	return (F(L)+F(R)+4*F(mid))*(R-L)/6;
}
double Solve(double L,double R,double eps){
	double mid=(L+R)/2,ans=Simpson(L,R);
	double l=Simpson(L,mid),r=Simpson(mid,R);
	if(fabs(l+r-ans)<eps)return l+r+(l+r-ans);
	return Solve(L,mid,eps/2)+Solve(mid,R,eps/2);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	double L,R;
	scanf("%lf%lf%lf%lf%lf%lf",&a,&b,&c,&d,&L,&R);
	printf("%.6lf\n",Solve(L,R,1e-8));
	return 0;
}