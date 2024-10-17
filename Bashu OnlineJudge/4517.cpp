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
int n,a[45][45];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	cin>>n;
	int i=1,j=n/2+1,k=1;
	while(k<=n*n){
		a[i][j]=k;
		i--;j++;
		if(i==0)i=n;
		if(j==n+1)j=1;
		if(a[i][j]!=0){
			i+=2;j--;
			if(j==0)j=n;
			if(i>n)i-=n;
		}
		k++;
	}
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			cout<<a[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}