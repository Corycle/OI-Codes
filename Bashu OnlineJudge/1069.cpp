#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
int main(){
	double a,i,s=0;
	cin>>a;
	for(i=1;i<=1000000000;i++){
		s+=1.0/i;
		if(s<=a&&s+1.0/(i+1)>a){
			cout<<i+1;break;
		}
	}
	return 0;
}