#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
using namespace std;
void mf(int n){
	int b[105]={0},x,i;
	i=x=0;
	while(n!=0){
		b[i++]=n%2;
		if(n%2==1)x++;
		n/=2;
	}
	for(;i>=0;i--){
		if(b[i]==1){
			if(i==0)cout<<"2(0)";
			else if(i==1)cout<<2;
			else if(i>=2){
				cout<<"2(";
				mf(i);
				cout<<")";
			}
			if(x>1){
				cout<<"+";
				x--;
			}
		}
	}
}
int main(){
	int n;
	cin>>n;
	mf(n);
	return 0;
}
