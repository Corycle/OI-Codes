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
struct _{
	int x,y;
}a[2505];
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
long long n,m,f[2505];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k,l;
	cin>>n;
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			cin>>k;
			a[k].x=i;a[k].y=j;
		}
	}
	for(i=2;i<=n*n;i++){
		for(j=1;j<i;j++){
			long long v=pow(abs(a[i].x-a[j].x)+abs(a[i].y-a[j].y),2);
			f[i]=max(f[i],f[j]+v);
		}
	}
	cout<<f[n*n];
	return 0;
}