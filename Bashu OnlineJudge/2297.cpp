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
long long n,v,w[105],u[105],f[10005][105];
int main(){
	int i,j,k;
	cin>>v>>n;
	for(i=1;i<=n;i++){
		cin>>w[i]>>u[i];
	}
	for(i=1;i<=v;i++){
		for(j=1;j<=n;j++){
			f[i][j]=f[i][j-1];
			if(i>=w[j])f[i][j]=max(f[i][j],f[i-w[j]][j-1]+u[j]);
		}
	}
	cout<<f[v][n];
	return 0;
}