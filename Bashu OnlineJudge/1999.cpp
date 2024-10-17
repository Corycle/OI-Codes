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
int n,m,p[2005];
double f[2005][2005],d[2005],minn;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k,x,y,z;
	cin>>n>>m;
	for(i=1;i<=m;i++){
		cin>>x>>y>>z;
		f[x][y]=f[y][x]=(100-z)/100.0;
	}
	cin>>x>>y;
	for(i=1;i<=n;i++)d[i]=f[x][i];
	d[x]=1;p[x]=1;
	for(i=1;i<=n;i++){
		minn=0;
		k=0;
		for(j=1;j<=n;j++){
			if(p[j]==0&&d[j]>minn){
				k=j;minn=d[j];
			}
		}
		p[k]=1;
		if(k==y||k==0)break;
		for(j=1;j<=n;j++){
			if(p[j]==0&&d[k]*f[k][j]>d[j]){
				d[j]=d[k]*f[k][j];
			}
		}
	}
	printf("%.8lf",100/d[y]);
	return 0;
}