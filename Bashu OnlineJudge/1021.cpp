#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
int main(){
	int a[101],n,i,j,k;
	memset(a,0,sizeof(a));
	cin>>n;cout<<n<<endl;
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++)
		if(j==i)continue;
		else if(a[j]==0)a[j]=1;
		else a[j]=0;
		for(j=1;j<=n;j++)cout<<a[j];
		cout<<endl;
	}
	return 0;
}