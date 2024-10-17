#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
int f[10]={6,2,5,5,4,5,6,3,7,6};
int gs(int x){
	int y=0;
	do{
		y+=f[x%10];
		x/=10;
	}while(x!=0);
	return y;
}
int main(){
    int i,j,k,n,s=0,a,b,c;
    cin>>n;
    n-=4;
    for(i=0;i<=1111;i++){
    	for(j=0;j<=1111;j++){
    		k=i+j;
			a=gs(i);
			b=gs(j);
			c=gs(k);
			if(a+b+c==n)s++;	
		}
	}
	cout<<s;
    return 0;
}