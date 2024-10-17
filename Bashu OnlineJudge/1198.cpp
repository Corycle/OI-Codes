#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
using namespace std;
char x[205],y[205];
int a[205][205],s[205][205],xx,yy,i,j;
void print(int l1,int l2){
	if(s[l1][l2]==1){
		print(l1-1,l2-1);
		printf("%c",x[l1-1]);
	}
	if(s[l1][l2]==2)print(l1-1,l2);
	if(s[l1][l2]==3)print(l1,l2-1);
}
int main(){
	cin>>x>>y;
	xx=strlen(x);
	yy=strlen(y);
	for(i=1;i<=xx;i++){
		for(j=1;j<=yy;j++){
			if(x[i-1]==y[j-1]){
				a[i][j]=a[i-1][j-1]+1;
				s[i][j]=1;
			}
			else{
				if(a[i-1][j]>a[i][j-1]){
					a[i][j]=a[i-1][j];
					s[i][j]=2;
				}
				if(a[i-1][j]<=a[i][j-1]){
					a[i][j]=a[i][j-1];
					s[i][j]=3;
				}
			}
		}
	}
	cout<<a[xx][yy]<<endl;
	print(xx,yy);
//	cout<<endl<<"GTCGTCGGAAGCCGGCCGAA";
	return 0;
}