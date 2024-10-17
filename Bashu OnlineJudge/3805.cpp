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
int n,w,a[20],f[20],dp[20],ans;
void init(){
	int i,j,k;
	scanf("%d%d",&n,&w);
	for(i=1;i<=n;i++){
		scanf("%d",&a[i]);
		ans+=a[i];
	}
}
void solve(){
	int i,j,k;
	if(ans%w==0)printf("%d",ans/w);
	else printf("%d",ans/w+1);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	init();
	solve();
	return 0;
}