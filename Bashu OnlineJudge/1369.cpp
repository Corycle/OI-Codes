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
int n,m,a[105],g[105],f[105][105],s[105][105],x[105],y[105];
int main(){
    int i,j,k,l;
    cin>>n>>m;
    for(i=1;i<=n;i++){
    	cin>>a[i];
    	g[i]=g[i-1]+a[i];
    	f[i][1]=g[i];
	}
	for(i=1;i<=n;i++){
		for(j=2;j<=m;j++){
			f[i][j]=0xfffff;
			for(k=s[i][j-1];k<i;k++){
				if(max(f[k][j-1],g[i]-g[k])<f[i][j]){
					f[i][j]=max(f[k][j-1],g[i]-g[k]);
					s[i][j]=k;
				}
			}
		}
	}
	cout<<f[n][m]<<endl;
	k=s[n][m];
	l=m;
	x[l+1]=n+1;
	while(l!=0){
		x[l]=k+1;
		y[l]=x[l+1]-1;
		l--;
		k=s[k][l];
	}
	for(i=1;i<=m;i++){
		cout<<x[i]<<" "<<y[i]<<endl;
	}
    return 0;
}