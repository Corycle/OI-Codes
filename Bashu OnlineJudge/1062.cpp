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
int n,m,a[105],g[105],f1[105][105][15],f2[105][105][15];//1min,2max;
int s1[105][105][15],s2[105][105][15],p[105][105],minn=0xffffff,maxx=-0xffffff;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k,l;
	cin>>n>>m;
	for(i=1;i<=n;i++){
		cin>>a[i];
		a[i+n]=a[i];
	}
	for(i=1;i<=n*2;i++){
		g[i]=g[i-1]+a[i];
	}
	for(i=1;i<=n*2;i++){
		for(j=i;j<=n*2;j++){
			p[i][j]=(g[j]-g[i-1])%10;
			if(p[i][j]<0)p[i][j]+=10;
			f1[i][j][1]=f2[i][j][1]=p[i][j];
			s1[i][j][1]=s2[i][j][1]=i-1;
		}
	}
	for(i=1;i<=n*2;i++){
		for(j=i+1;j<=n*2;j++){
			for(l=2;l<=m;l++){
				f1[i][j][l]=0xfffffff;
				f2[i][j][l]=-0xffffff;
				for(k=s1[i][j][l-1]+1;k<j;k++){
					if(f1[i][j][l]>(f1[i][k][l-1])*(p[k+1][j])){
						f1[i][j][l]=(f1[i][k][l-1])*(p[k+1][j]);
						s1[i][j][l]=k;
					}
				}
				for(k=s2[i][j][l-1]+1;k<j;k++){
					if(f2[i][j][l]<(f2[i][k][l-1])*(p[k+1][j])){
						f2[i][j][l]=(f2[i][k][l-1])*(p[k+1][j]);
						s2[i][j][l]=k;
					}
				}
			}
		}
	}
	for(i=1;i<=n;i++){
		minn=min(minn,f1[i][i+n-1][m]);
		maxx=max(maxx,f2[i][i+n-1][m]);
	}
	if(minn<=0)cout<<0;
	else cout<<minn;
	cout<<endl<<maxx;
	return 0;
}