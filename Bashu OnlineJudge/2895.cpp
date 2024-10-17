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
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int a[105][105],ans,m,n;
int main(){
	int i,j,k,l;
	scanf("%d%d",&n,&m);
	memset(a,0xf,sizeof(a));
	for(i=1;i<=n;i++)a[i][i]=0;
	for(i=1;i<=m;i++){
		scanf("%d%d%d",&j,&k,&l);
		a[j][k]=a[k][j]=l;
	}
	for(k=1;k<=n;k++){
		for(i=1;i<=n;i++){
			for(j=1;j<=n;j++){
				a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
			}
		}
	}
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			ans=max(ans,a[i][j]);
		}
	}
	printf("%d",ans);
	return 0;
}