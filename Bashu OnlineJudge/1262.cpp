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
int f[10][45],g[45][45],a[45],n,k;
void huan(int x,int y){
	int i;
	for(i=x;i<=y;i++){
		g[x][y]=g[x][y]*10+a[i];
	}
}
int main(){
	int i,j,t,maxx;
	char c;
	cin>>n>>k;
	for(i=1;i<=n;i++){
		cin>>c;
		a[i]=c-'0';
	}
	for(i=1;i<=n;i++){
		for(j=i;j<=n;j++){
			huan(i,j);
		}
	}
	for(i=1;i<=n;i++)f[0][i]=g[1][i];
	for(i=1;i<=k;i++){
		for(j=i+1;j<=n;j++){
			maxx=0;
        	for(t=i;t<=j-1;t++)
        		if(f[i-1][t]*g[t+1][j]>maxx)maxx=f[i-1][t]*g[t+1][j];
        	f[i][j]=maxx;
		}
	}
	cout<<f[k][n]<<endl;
	return 0;
}