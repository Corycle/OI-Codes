#include<iostream>
#include<iomanip>//50
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
using namespace std;
int main(){
	int n;
	cin>>n;
	int a[n+1],i,j;
	for(i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	j=1;
	for(i=1;i<=n;i++)
	{	if(i==1)cout<<a[i]<<" ";
		else if(a[i]==a[i-1])j++;
		else if(a[i]!=a[i-1]){cout<<j<<endl<<a[i]<<" ";j=1;}
		if(i==n)cout<<j;}
	return 0;
}