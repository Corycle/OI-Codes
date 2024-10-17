#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
using namespace std;
int n,i,j,k,l,top,dzh[50],f[10];
char a;
int main(){
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a;
		if(a=='A'){
			l++;k++;
			dzh[k]=l;
		}
		if(a=='B'){
			top++;
			l++;
			f[top]=l;
			if(top>5){
				cout<<"No";
				return 0;
			}
		}
		if(a=='C'){
			top--;k++;
			dzh[k]=f[top+1];
			f[top+1]=0;
			if(top<0){
				cout<<"No";
				return 0;
			}
		}
	}
	cout<<"Yes"<<endl;
	for(i=1;i<=k;i++)cout<<dzh[i]<<endl;
	return 0;
}