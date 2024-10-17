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
int n;
int a[105];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	cin>>n;
	for(i=n;i>=0;i--){
		cin>>a[i];
	}
	for(i=n;i>=0;i--){
		if(a[i]==0)continue;
		if(a[i]>0&&i!=n)cout<<'+';
		if(i!=0){
			if(abs(a[i])!=1)cout<<a[i];
			else if(a[i]==-1)cout<<"-";
			cout<<"x";
		}
		if(i>1)cout<<"^"<<i;
		if(i==0)cout<<a[i];
	}
	return 0;
}