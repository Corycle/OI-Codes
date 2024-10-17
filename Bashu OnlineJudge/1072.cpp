#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
long long a[24][24],f[24][24];
int main(){
	int x1,x2,x3,x4;
	cin>>x1>>x2>>x3>>x4;
for(int i=0;i<=x1;i++)
	for(int j=0;j<=x2;j++)
	 a[i][j]=1;

	a[x3][x4]=0;
if(x3>=2&&x4>=1)a[x3-2][x4-1]=0;
if(x3>=1&&x4>=2)	a[x3-1][x4-2]=0;
	if(x4>=2)a[x3+1][x4-2]=0;
	if(x4>=1)a[x3+2][x4-1]=0;
	a[x3+2][x4+1]=0;
	a[x3+1][x4+2]=0;
	if(x3>=1)a[x3-1][x4+2]=0;
	if(x3>=2)a[x3-2][x4+1]=0;
	for(int i=0;i<=x1;i++){
		for(int j=0;j<=x2;j++){
			if(a[i][j]==0)continue;
			if(i==0&&j==0)continue;
			else if(i==0)a[i][j]=a[i][j-1];
			else if(j==0)a[i][j]=a[i-1][j];
			else {
				a[i][j]=a[i-1][j]+a[i][j-1];
			}
		}
	}
	cout<<a[x1][x2];
	return 0;
	
	
	
	
} 