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
int m,n,f[10][10][10][10],a[10][10];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k,x1,x2,y1,y2,t;
	cin>>n;
	while(cin>>i>>j>>k){
		if(i==0&&j==0&&k==0)break;
		a[i][j]=k;
	}
	for(x1=1;x1<=n;x1++){
		for(y1=1;y1<=n;y1++){
			for(x2=1;x2<=n;x2++){
				for(y2=1;y2<=n;y2++){
					t=max(f[x1][y1][x2][y2],max(max(f[x1-1][y1][x2-1][y2],f[x1][y1-1][x2][y2-1]),max(f[x1-1][y1][x2][y2-1],f[x1][y1-1][x2-1][y2])));
					if(x1==x2&&y2==y1)t+=a[x1][y1];
					else t+=a[x1][y1]+a[x2][y2];
					f[x1][y1][x2][y2]=max(f[x1][y1][x2][y2],t);
				}
			}
		}
	}
	cout<<f[n][n][n][n];
	return 0;
}