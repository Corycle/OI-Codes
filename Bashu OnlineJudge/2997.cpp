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
int n,f[200005][5],a[200005][5];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a[i][1]>>a[i][2]>>a[i][3];
		f[i][1]=a[i][1]+min(f[i-1][2],f[i-1][3]);
		f[i][2]=a[i][2]+min(f[i-1][1],f[i-1][3]);
		f[i][3]=a[i][3]+min(f[i-1][2],f[i-1][1]);
	}
	cout<<min(f[n][1],min(f[n][2],f[n][3]));
	return 0;
}
