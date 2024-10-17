#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
using namespace std;
//struct _{};
//stack<_>_;
//queue<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int a[1005][1005],n,m,s;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	cin>>n>>m;
	int i,j,k;
	char l;
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			cin>>l;
			a[i][j]=l-'0';
			if(a[i][j]!=0)s+=2;
		}
	}
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			if(a[i][j]>a[i-1][j])s+=a[i][j]-a[i-1][j];
			if(a[i][j]>a[i][j-1])s+=a[i][j]-a[i][j-1];
			if(a[i][j]>a[i+1][j])s+=a[i][j]-a[i+1][j];
			if(a[i][j]>a[i][j+1])s+=a[i][j]-a[i][j+1];
		}
	}
	cout<<s;
	return 0;
}
