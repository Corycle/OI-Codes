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
int n,m,a1[105],x[105],y[105],z[105],f[105][2005];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	cin>>n>>m;
	for(i=1;i<=n;i++){
		cin>>a1[i];
		if(a1[i]==1){
			cin>>x[i]>>y[i];
		}
		if(a1[i]==2){
			cin>>x[i]>>y[i]>>z[i];
		}
		if(a1[i]==3){
			cin>>x[i]>>y[i];
		}
	}
	for(j=1;j<=m;j++){
		for(i=1;i<=n;i++){
			if(a1[i]==1){
				f[i][j]=f[i-1][j];
				for(k=0;k<=j;k++){
					f[i][j]=max(f[i][j],int(f[i-1][j-k]+x[i]*pow(k,2)-k*y[i]));
				}
			}
			if(a1[i]==2){
				f[i][j]=f[i-1][j];
				for(k=1;k<=z[i];k++){
					if(k*y[i]<=j){
						f[i][j]=max(f[i][j],f[i-1][j-k*y[i]]+k*x[i]);
					}
				}
			}
			if(a1[i]==3){
				f[i][j]=max(f[i-1][j],f[i][j-1]);
				if(j>=y[i]){
					f[i][j]=max(f[i][j],max(f[i-1][j-y[i]]+x[i],f[i][j-y[i]]+x[i]));
				}
			}
		}
	}
	cout<<f[n][m];
	return 0;
}