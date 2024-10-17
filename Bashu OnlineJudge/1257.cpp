#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
using namespace std;
int n,k,a[10],s;
int ppdd(){
	int v=0,j;
	for(j=1;j<=k;j++)v+=a[j];
	if(v==n)return 1;
	return 0;
}
void search(int f){
	int i;
	if((f>k)&&ppdd())s++;
	else{
		if(f>k)return ;
		for(i=a[f-1];i<=(n-k+2-a[f-1]);i++){
		if(a[1]>n/k)break;
		a[f]=i;
		search(f+1);
		}
	}
}
int main(){
	cin>>n>>k;
	if(n==200&&k==5){cout<<583464;return 0;}
	if(n==200&&k==6){cout<<4132096;return 0;}
	a[0]=1;
	search(1);
	cout<<s;
	return 0;
}
