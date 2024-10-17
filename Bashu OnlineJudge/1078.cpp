#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<cstdlib>
#include<algorithm>
using namespace std;
int n,a[1005][5];
int main(){
//	freopen("order.in","r",stdin);
//	freopen("order.out","w",stdout);
	int i,j,k,l;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a[i][1];
		a[i][2]=1;
		a[i][3]=0;
	}
	for(i=n-1;i>=1;i--){
		l=k=0;
		for(j=i+1;j<=n;j++){
			if(a[j][1]>=a[i][1]&&a[j][2]>l){
				l=a[j][2];
				k=j;
			}
		}
		if(l>0){
			a[i][2]=l+1;
			a[i][3]=k;
		}
	}
	k=1;
	for(j=1;j<=n;j++){
		if(a[j][2]>a[k][2])k=j;
	}
	cout<<a[k][2];
	return 0;
}