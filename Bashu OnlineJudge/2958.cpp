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
long long a[1005][1005],f2[1005][1005],f5[1005][1005];
int m,n;
int nd(long long f,int t){
	int s=0;
	while(f%t==0){
		s++;
		f/=t;
	}
	return s;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
//	cout<<nd(8,2);
	int i,j,k;
	cin>>n>>m;
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			cin>>a[i][j];
			if(i==1){
				f2[1][j]=f2[1][j-1]+nd(a[i][j],2);
				f5[1][j]=f5[1][j-1]+nd(a[i][j],5);
			}
			if(j==1){
				f2[i][1]=f2[i-1][1]+nd(a[i][j],2);
				f5[i][1]=f5[i-1][1]+nd(a[i][j],5);
			}
		}
	}
	for(i=2;i<=n;i++){
		for(j=2;j<=m;j++){
			f2[i][j]=min(f2[i][j-1],f2[i-1][j])+nd(a[i][j],2);
			f5[i][j]=min(f5[i][j-1],f5[i-1][j])+nd(a[i][j],5);
		}
	}
//	for(i=1;i<=n;i++){
//		for(j=1;j<=m;j++){
//			cout<<f2[i][j]<<" ";
//		}
//		cout<<endl;
//	}
//	for(i=1;i<=n;i++){
//		for(j=1;j<=m;j++){
//			cout<<f5[i][j]<<" ";
//		}
//		cout<<endl;
//	}
	cout<<min(f2[n][m],f5[n][m]);
	return 0;
}