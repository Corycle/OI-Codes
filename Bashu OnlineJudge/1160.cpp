#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
int main(){
	double x1,x2,x3,y1,y2,y3,s,a,b,c,p;
	cin>>x1>>y1>>x2>>y2>>x3>>y3;
	a=sqrt(pow(abs(x1-x2),2)+pow(abs(y1-y2),2));
	b=sqrt(pow(abs(x2-x3),2)+pow(abs(y2-y3),2));
	c=sqrt(pow(abs(x1-x3),2)+pow(abs(y1-y3),2));
	p=(a+b+c)/2.0;
	s=sqrt(p*(p-a)*(p-b)*(p-c));
	printf("%.2lf",s);
}