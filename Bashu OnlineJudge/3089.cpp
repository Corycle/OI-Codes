#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
using namespace std;
//struct _{};
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
double pi=3.1415926535;
double f[1005][1005],x[1005],y[1005],ans=0xfffffff,p;
int n;
double dist(int i,int j){
	return sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])) ;  
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%lf%lf",&x[i],&y[i]);
	}
	for(i=1;i<=n;i++){
		p=0;
		for(j=1;j<=n;j++){
			p=max(p,dist(i,j));
		}
		ans=min(p,ans);
	}
	printf("%.4lf",ans*ans*pi);
	return 0;
}