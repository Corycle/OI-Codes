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
const double eps=1e-8;
const double INF=9e18;
const int N=500005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n;
double T,a[N],b[N],sum1[N],sum2[N];
int Sgn(double x){
	if(x>eps)return 1;
	if(x<-eps)return -1;
	return 0;
}
double Check(double a1,double a2,double b1,double b2){
	double x=0,t1=0,t2=0;
	double sum1=INF,sum2=INF;
	if(!Sgn(a1)||!Sgn(b1))sum1=0;
	if(!Sgn(a2)||!Sgn(b2))sum2=0;
	if(!Sgn(sum1)&&!Sgn(sum2))return 0;
	if(Sgn(sum1)&&!Sgn(sum2)){
		x=b1/a1;t1=T/(1+x);t2=T-t1;
		return max(a1*t1,b1*t2);
	}
	if(Sgn(sum2)&&!Sgn(sum1)){
		x=b2/a2;t1=T/(1+x);t2=T-t1;
		return max(a2*t1,b2*t2);
	}
	double l=max(T*(b1-a2)/(a1+b1),0.0);
	double r=min(T*(b1+b2)/(a1+b1),T);
	double k=a1-a2*(a1+b1)/(a2+b2);
	t1=Sgn(k)>0?l:r;
	t2=((b1+b2)*T-(a1+b1)*t1)/(a2+b2);
	return max(a1*t1+a2*t2,b1*(T-t1)+b2*(T-t2));
}
int main(){
//	freopen("artist.in","r",stdin);
//	freopen("artist.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		scanf("%lf%lf",&a[i],&b[i]);
		sum1[i]=sum1[i-1]+a[i];
		sum2[i]=sum2[i-1]+b[i];
	}
	scanf("%lf",&T);
	double Ans=INF;
	for(int i=1;i<=n;i++){
		double a1=sum1[i],a2=sum1[n]-sum1[i];
		double b1=sum2[i],b2=sum2[n]-sum2[i];
		Ans=min(Ans,Check(a1,a2,b1,b2));
	}
	printf("%.2lf",Ans);
	return 0;
}