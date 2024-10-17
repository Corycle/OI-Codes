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
int n;
double f[800005],a[800005];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%lf",&a[i]);
	}
	for(i=1;i<=n+1;i++){
		f[i]=max(f[i],f[i-1]);
		f[i]=max(f[i],f[i-1]+a[i]);
		if(i>=2)f[i]=max(f[i],f[i-2]+a[i-1]*a[i-1]);
	}
	printf("%.4lf",f[n+1]);
	return 0;
}