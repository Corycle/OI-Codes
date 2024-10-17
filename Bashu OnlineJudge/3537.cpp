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
//stack<_>_;
//queue<int>q;
//priority_queue<_>f;
//priority_queue<_,vector<int>,greater<int> >f;
int n,m,a[105],ans,f[105][105];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	cin>>n>>m;
	for(i=1;i<=n;i++){
		cin>>a[i];
	}
	for(i=0;i<=a[1];i++){
		f[1][i]=1;
	}
	for(i=2;i<=n;i++){
		for(j=0;j<=m;j++){
			for(k=0;k<=min(a[i],j);k++){
				f[i][j]=(f[i-1][j-k]+f[i][j])%1000007;
			}
		}
	}
	cout<<f[n][m];
	return 0;
}