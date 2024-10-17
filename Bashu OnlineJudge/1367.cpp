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
const int N=10005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n;
int a[N],b[N],c[N];
double S(int i,double x){
	return a[i]*x*x+b[i]*x+c[i];
}
double F(double x){
	double Max=-inf;
	for(int i=1;i<=n;i++){
		Max=max(Max,S(i,x));
	}
	return Max;
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
	int T=read();
	while(T--){
		n=read();
		for(int i=1;i<=n;i++){
			a[i]=read();
			b[i]=read();
			c[i]=read();
		}
		double ans=Solve(0,1000);
		printf("%.4lf\n",F(ans));
	}
	return 0;
}