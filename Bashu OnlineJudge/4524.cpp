#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
using namespace std;
char a[105][105];
int n,m,i,j,k,l;
int main(){
	memset(a,'?',sizeof(a));
	cin>>n>>m;
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			cin>>a[i][j];
		}
	}
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			k=0;
			if(a[i][j]=='*')continue;
			else{
				if(a[i-1][j-1]=='*')k++;
				if(a[i-1][j]=='*')k++;
				if(a[i-1][j+1]=='*')k++;
				if(a[i+1][j-1]=='*')k++;
				if(a[i+1][j]=='*')k++;
				if(a[i+1][j+1]=='*')k++;
				if(a[i][j-1]=='*')k++;
				if(a[i][j+1]=='*')k++;
			}
			a[i][j]=char(k+'0');
		}
	}
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			cout<<a[i][j];
		}
		cout<<endl;
	}
	return 0;
}