#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cmath>
using namespace std;
int a[10001],s;
bool b=true;
int pd(int s){
	int y;
	for(y=2;y*y<=s;y++)
	if(s%y==0)return -1;
	return 1;
}
void print(int n,int h){
	for(int i=1;i<=h-1;i++)
	printf("%d*",a[i]);
	printf("%d\n",n);
}	
void search(int n,int h){
	if(n<=0||b==false)return ;
	if(pd(n)==1){
		print(n,h);
		b=false;
	}
	if(b==false)return;
	for(int i=a[h-1];i<=n/2;i++){
		if(pd(i)==1&&i>=2&&n%i==0){
			a[h]=i;
			search(n/i,h+1);
			}
		}
	}
	int main(){
	while(cin>>s){
		a[0]=2;
		search(s,1);
		b=true;
	}
	return 0;
}