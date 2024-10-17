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
priority_queue<int>q;
priority_queue<int,vector<int>,greater<int> >ans;
int n,m,a[10005],b[10005],c[10005];
int f(int num,int t){
	return a[t]*num*num+b[t]*num+c[t];
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++){
		scanf("%d%d%d",&a[i],&b[i],&c[i]);
	}
	for(j=1;j<=m;j++)q.push(f(j,1));
	for(i=1;i<=m;i++){
		for(j=2;j<=n;j++){
			k=f(i,j);
			if(q.top()>=k){
				q.pop();
				q.push(k);
			}
		}
	}
	k=m;
	while(k--){
		ans.push(q.top());
		q.pop();
	}
	while(m--){
		printf("%d ",ans.top());
		ans.pop();
	}
	return 0;
}