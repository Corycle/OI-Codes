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
const double eps=1e-10;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
double a,b;
double Sqr(double x){return x*x;}
double F(double x){
	return sqrt(a*(1-Sqr(x)/b));
}
double Simpson(double L,double R){
	double mid=(L+R)/2;
	return (F(L)+F(R)+4*F(mid))*(R-L)/6;
}
double Solve(double L,double R){
	double mid=(L+R)/2;
	if(abs(Simpson(L,mid)+Simpson(mid,R)-Simpson(L,R))<eps)return Simpson(L,R);
	return Solve(L,mid)+Solve(mid,R);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		double L,R;
		scanf("%lf%lf%lf%lf",&L,&R,&a,&b);
		printf("%.8lf\n",Solve(L,R));
	}
	return 0;
}