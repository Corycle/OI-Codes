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
const double eps=1e-13;
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n;
double a[N][N],Ans;
void Solve(){
	int m=n-1;
	for(int i=1;i<=m;i++){
		int t=i;
		double Max=abs(a[i][i]);
		for(int j=i+1;j<=m;j++){
			if(abs(a[j][i])>Max){
				Max=abs(a[j][i]);t=j;
			}
		}
		if(i!=t){swap(a[i],a[t]);Ans=-Ans;}
		if(fabs(a[i][i])<eps)return;
		for(int j=i+1;j<=m;j++){
			double dlt=a[j][i]/a[i][i];
			for(int k=i;k<=m;k++){
				a[j][k]-=a[i][k]*dlt;
			}
		}
		Ans*=a[i][i];
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Ans=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			double x;
			scanf("%lf",&x);
			if(i<j){
				if(fabs(x-0)<eps)x=eps;
				if(fabs(x-1)<eps)x=1-eps;
				Ans*=(1-x);x=x/(1-x);
				a[i][i]+=x;a[j][j]+=x;
				a[i][j]-=x;a[j][i]-=x;
			}
		}
	}
	Solve();
	printf("%.10lf",Ans+eps);
	return 0;
}