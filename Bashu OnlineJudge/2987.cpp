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
int n,m,a[105][105],l;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	scanf("%d%d",&n,&m);
	memset(a,0xf,sizeof(a));
	for(i=1;i<=m;i++){
		scanf("%d%d%d",&j,&k,&l);
		a[j][k]=a[k][j]=l;
	}
	for(i=1;i<=n;i++)a[i][i]=0;
	for(k=1;k<=n;k++){
		for(i=1;i<=n;i++){
			for(j=1;j<=n;j++){
				a[i][j]=min(a[i][k]+a[k][j],a[i][j]);
			}
		}
	}
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}
	return 0;
}