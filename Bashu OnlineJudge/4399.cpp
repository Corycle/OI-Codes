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
const int N=10005;
const double D=0.97;
const double eps=1e-14;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
double bx,by,Ans,Best;
int n,m,X[N],Y[N],w[N];
double Random(double T){return T*(rand()*2-RAND_MAX);}
double Calc(double x,double y){
	double ans=0;
	for(int i=1;i<=n;i++){
		double dx=X[i]-x,dy=Y[i]-y;
		ans+=sqrt(dx*dx+dy*dy)*w[i];
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	srand(time(NULL));
	for(int i=1;i<=n;i++){
		X[i]=read();Y[i]=read();w[i]=read();
		bx+=X[i];by+=Y[i];
	}
	bx/=n;by/=n;
	Ans=Best=Calc(bx,by);
	int Times=3;
	while(Times--){
		double x=bx,y=by;Ans=Best;
		for(double T=1e4;T>eps;T*=D){
			double fx=x+Random(T),fy=y+Random(T);
			double tmp=Calc(fx,fy);
			if(Best>tmp){Best=tmp;bx=fx;by=fy;}
			if(Ans>tmp||exp((tmp-Ans)/T)<((double)rand()/RAND_MAX)){Ans=tmp;x=fx;y=fy;}
		}
	}
	printf("%.2lf %.2lf",bx,by);
	return 0;
}