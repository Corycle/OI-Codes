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
int pd(int f){
	int i,j,k;
	for(i=2;i*i<=f;i++){
		if(f%i==0)return 0;
	}
	return 1;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	cin>>n;
	int i,j,k=0;
	for(i=2;i*i<=n;i++){
		if(n%i==0){
			if(pd(i)){
				cout<<n/i;
				return 0;
			}
		}
	}
	return 0;
}