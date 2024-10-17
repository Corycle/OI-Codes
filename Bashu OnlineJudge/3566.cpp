#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
using namespace std;
int n,i,j,k,l,dzh,top;
char a[1000005];
int main(){
	cin>>n;
	for(i=1;i<=n;i++){
		dzh=0;
		cin>>a;
		top=strlen(a)-1;
		for(j=0;j<=top;j++){
			if(a[j]=='#')dzh=j+1;
			if(a[j]=='$'){
				if(a[j-1]=='#'||a[j-1]=='$')dzh++;
				else{
					for(l=j-1;l<=top;l++){
						a[l]=a[l+2];
					}
					top-=2;
					j-=2;
				}
			}
		}
		for(dzh;dzh<=top;dzh++){
			cout<<a[dzh];
		}
		cout<<endl;
	}
	return 0;
}