#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
using namespace std;
int main(){
	int n,a[4],b[4],s=100000000,i,j;
	cin>>n;
	for(i=1;i<=3;i++){
		cin>>a[i]>>b[i];
		if(n%a[i]==0)j=n/a[i];
		else j=n/a[i]+1;
		j*=b[i];
		s=min(s,j);
	}
	cout<<s;
	return 0;
}
