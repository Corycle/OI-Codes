#include<iostream>
using namespace std;
long long f[1000005];
int main(){
	f[1]=1;
	f[2]=1;
	f[3]=2;
	int k;
	while(cin>>k){
		for(int i=3;;i++){
		f[i]=f[i-1]+f[i-2];
		if(f[i]>k){
			printf("%lld\n",f[i-2]*f[i-2]+f[i-1]*f[i-1]);
			break;
		}
	}
	}
}