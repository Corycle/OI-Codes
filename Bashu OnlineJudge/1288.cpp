#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
using namespace std;
int main(){
	char a[50],b,x,y;
	int n,i,j,k;
	memset(a,32,sizeof(a));
	
	cin.getline(a,sizeof(a));
	
	cin>>n;
	
	for(i=1;i<=n;i++){
		cin>>b;
		if(b=='D'){
			cin>>x;
			for(j=0;j<=49;j++)
			if(a[j]==x){
				for(k=j;k<=48;k++)
				a[k]=a[k+1];
				break;
			}
		}
		else if(b=='I'){
			cin>>x>>y;
			for(j=49;j>=0;j--)
			if(a[j]==x){
				for(k=49;k>j;k--)
				a[k]=a[k-1];
				a[j]=y;
				break;
			}
		}
		else if(b=='R'){
			cin>>x>>y;
			for(j=0;j<=49;j++)
			if(a[j]==x)
			a[j]=y;
		}
	}

	for(i=0;i<=49;i++){
		cout<<a[i];
		if(a[i]=='.'||a[i]=='%')return 0;
	}
	
	return 0;
}
