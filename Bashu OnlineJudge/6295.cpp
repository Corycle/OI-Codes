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
const int N=300005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n;
double a[N],b[N];
double F(double x){
	double ans=0;
	for(int i=1;i<=n;i++){
		ans+=fabs(a[i]*x+b[i]);
	}
	return ans;
}
int main(){
//	freopen("spongebob.in","r",stdin);
//	freopen("spongebob.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		b[i]=read();
	}
	double l=-inf,r=inf;
	while(r-l>eps){
		double mid1=l+(r-l)/3;
		double mid2=r-(r-l)/3;
		double c1=F(mid1),c2=F(mid2);
		if(c1<c2)r=mid2;else l=mid1;
	}
	printf("%.5lf",F(l));
	return 0;
}