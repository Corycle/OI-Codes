#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
using namespace std;
int n,a[105],b[105],c[105],maxx;
int main(){
	cin>>n;
	int i,j,k,l;
	for(i=1;i<=n;i++)cin>>a[i];
	for(i=1;i<=n;i++){
		b[i]=1;
		for(j=1;j<i;j++){
			if(a[i]>a[j]&&b[j]+1>b[i])
			b[i]=b[j]+1;
		}
	}
	for(i=n;i>=1;i--){
		c[i]=1;
		for(j=n;j>i;j--){
			if(a[i]>a[j]&&c[j]+1>c[i])
			c[i]=c[j]+1;
		}
	}
	for(i=1;i<=n;i++)if(b[i]+c[i]>maxx)maxx=b[i]+c[i];
	cout<<n-maxx+1;
	return 0;
}