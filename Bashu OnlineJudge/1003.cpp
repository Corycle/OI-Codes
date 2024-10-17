#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
using namespace std;
char x[3005],y[3005];
int a[3005][3005],xx,yy,i,j;
int main(){
	cin>>x>>y;
	xx=strlen(x);
	yy=strlen(y);
	for(i=1;i<=xx;i++){
		for(j=1;j<=yy;j++){
			if(x[i-1]==y[j-1])a[i][j]=a[i-1][j-1]+1;
			else a[i][j]=max(a[i-1][j],a[i][j-1]);
		}
	}
	cout<<a[xx][yy];
	return 0;
}