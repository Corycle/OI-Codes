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
int n,m,a[1005],g0[1005],g1[1005],f[1005][65],c[1005][1005];
int main(){
    int i,j,k;
    char l;
    cin>>n>>m;
    for(i=1;i<=n;i++){
    	cin>>l;
    	a[i]=l-'0';
    	g0[i]=g0[i-1];
    	g1[i]=g1[i-1];
    	if(a[i]==0)g0[i]++;
    	if(a[i]==1)g1[i]++;
	}
	for(i=1;i<=n;i++){
		for(j=i;j<=n;j++){
			c[i][j]=(g0[j]-g0[i-1])*(g1[j]-g1[i-1]);
		}
	}
	for(i=1;i<=n;i++)f[i][1]=c[1][i];
	for(i=1;i<=n;i++){
		for(j=2;j<=m;j++){
			f[i][j]=0xfffff;  
			for(k=1;k<i;k++){
				f[i][j]=min(f[i][j],f[k][j-1]+c[k+1][i]);
			}
		}
	}
	cout<<f[n][m];
    return 0;
}