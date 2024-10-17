#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
using namespace std;
int main(){
//	freopen("t1.in","r",stdin);
//	freopen("t1.out","w",stdout);
	int a[13]={220,1184,2620,5020,6232,10744,12285,17296,63020,66928,67095,69615,79750};
	int b[13]={284,1210,2924,5564,6368,10856,14595,18416,76084,66992,71145,87633,88730};
	int x,y,v=0,i;
	cin>>x>>y;
	for(i=0;i<=12;i++)
	{	if(a[i]>=x&&a[i]<=y&&b[i]>=x&&b[i]<=y)
		{	printf("%d %d\n",a[i],b[i]);v++;}
		if(i==12&&v==0)cout<<"Sorry";}
	return 0;
}
