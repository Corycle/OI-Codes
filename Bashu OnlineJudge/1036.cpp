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
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
long long f[55];
int main(){  
    int n,i,j,k;
	f[1]=2;f[2]=3;
	for(i=3;i<=50;i++){
		f[i]=f[i-1]+f[i-2];
	}
	cin>>n;
	cout<<f[n];
    return 0;  
}