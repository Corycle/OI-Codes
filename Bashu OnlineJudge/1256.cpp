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
//stack<_>_;
//queue<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
double a,b,c,d;
double f(double x){
	return a*pow(x,3)+b*pow(x,2)+c*x+d;
}
void lll(double l,double r){
	double mid=(l+r)/2.0;
	if(r-l<=0.001&&l<=100&&f(l)*f(r)<0){
		printf("%.2lf ",(l+r)/2);
		return;
	}
	if(f(l)*f(mid)<0)lll(l,mid);
	if(f(r)*f(mid)<0)lll(mid,r);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	double i,j,k,l;
	cin>>a>>b>>c>>d;
	for(i=-100;i<=100;i++){
		if(f(i)==0)printf("%.2lf ",i);
		if(f(i)*f(i+1)<0)lll(i,i+1);
	}
	return 0;
}