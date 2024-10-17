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
priority_queue<int>q;
//priority_queue<int,vector<int>,greater<int> >q;
int n,a[100005],b[100005];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	cin>>n;
	for(i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(i=1;i<=n;i++){
		scanf("%d",&b[i]);
	}
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	for(i=1;i<=n;i++)q.push(a[1]+b[i]);
	for(i=2;i<=n;i++){
		for(j=1;j<=n;j++){
			if(q.top()>a[i]+b[j]){
				q.pop();
				q.push(a[i]+b[j]);
			}
			else break;
		}
	}
	for(i=n;i>=1;i--){
		a[i]=q.top();
		q.pop();
	}
	for(i=1;i<=n;i++)printf("%d ",a[i]);
	return 0;
}