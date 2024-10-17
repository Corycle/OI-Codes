#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
using namespace std;
long long f[100]={0};
long long num(long long x)
{	if(x==0)return 0;
	for(int i=91;i>=0;i--)
		if(f[i]<=x)return f[i-1]+num(x-f[i]);
}
int main(){
	long long q,x,y;
	f[0]=1;f[1]=1;
	for(int i=2;i<=91;i++)f[i]=f[i-1]+f[i-2];
	cin>>q;
	for(int i=1;i<=q;i++)
	{	cin>>x>>y;
	cout<<num(y)-num(x-1)<<endl;
	}
	return 0;
}