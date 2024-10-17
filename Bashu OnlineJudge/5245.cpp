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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
double c[N];
struct node{
	double x,y;
}a[N];
double Check(double x){
	double ans=0;
	for(int i=1;i<=n;i++){
		c[i]=a[i].x-x*a[i].y;
	}
	sort(c+1,c+n+1);
	for(int i=n-m+1;i<=n;i++)ans+=c[i];
	return ans;
}
double Erfen(){
	double l=0,r=1,ans=0;
	while(r-l>eps){
		double mid=(l+r)/2.0;
		if(Check(mid)>=0){
			ans=mid;
			l=mid;
		}
		else r=mid;
	}
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)scanf("%lf",&a[i].x);
	for(int i=1;i<=n;i++)scanf("%lf",&a[i].y);
	double ans=Erfen();
	printf("%.4lf\n",ans);
	return 0;
}