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
const double eps=1e-14;
const int N=10005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
double a,b,f,Vmax,len;
double Xi[N],Yi[N],K[N],dis[N];
double Sqr(double x){return x*x;}
bool Check(double v){
	double sum=0;
	for(int i=1;i<=n;i++){
		sum+=max((double)(0),a*v+b*K[i])*dis[i];
		if(sum-eps>f)return false;
	}
	if(sum-eps<f)return true;
	return false;
}
double Solve(){
	double l=0,r=Vmax;
	while(l+eps<r){
		double mid=(l+r)/2;
		if(Check(mid))l=mid;
		else r=mid;
	}
	return l;
}
double Ask(double v){
	double sum=0;
	for(int i=1;i<=n;i++){
		double s=a*v+b*K[i];
		if(s<eps)sum+=dis[i]/min(((-b*K[i])/a),Vmax);
		else sum+=dis[i]/v;
	}
	return sum;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		scanf("%lf%lf%lf%lf",&a,&b,&Vmax,&f);
		n=read();
		double x=0,y=0;
		for(int i=1;i<=n;i++){
			scanf("%lf%lf",&x,&y);
			K[i]=y/x;x/=1000;y/=1000;
			dis[i]=sqrt(Sqr(x)+Sqr(y));
		}
		double ans=Solve();
		if(abs(ans)<eps)printf("IMPOSSIBLE\n");
		else printf("%.5lf\n",Ask(ans));
	}
	return 0;
}