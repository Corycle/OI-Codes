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
int n,m,a[1005],f[1005][205],s[1005][205],ans=-0x7fffffff/2;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k,l;
	cin>>n>>m;
	for(i=1;i<=n;i++){
		cin>>a[i];
	}
	for(i=1;i<=n;i++){
		for(j=2;j<=m;j++){
			f[i][j]=-0x7fffffff/2;
		}
	}
	for(i=1;i<=n;i++){
		f[i][1]=max(f[i-1][1],0)+a[i];
	}
	for(j=2;j<=m;j++){
		for(i=j;i<=n;i++){
			f[i][j]=f[i-1][j]+a[i];
			for(k=j-1;k<i;k++){
				f[i][j]=max(f[i][j],f[k][j-1]+a[i]);
			}
		}
	}
	for(i=1;i<=n;i++)ans=max(ans,f[i][m]);
	cout<<ans;
	return 0;
}