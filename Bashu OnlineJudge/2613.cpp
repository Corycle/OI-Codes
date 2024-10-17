#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int main(){
	int n,b1;
	cin>>n;
	string a;
	int b[101];
	for(int i=1;i<=n;i++){
		cin>>a;
		b1=a[a.length()-1]-'0';
		if(b1%2==0)b[i]=1;
		if(b1%2!=0)b[i]=0;
	}
	for(int i=1;i<=n;i++){
		if(b[i]==1)cout<<"even"<<endl;
		if(b[i]==0)cout<<"odd"<<endl;
	}
return 0;
}