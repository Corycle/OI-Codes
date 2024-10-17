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
//struct _{};
using namespace std;
//stack<_>_;
//queue<int>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int ans=-0xffffff,sum[200005],num[200005],q[200005],head=1,rear=1,n,i,j,m,x;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	cin>>n;m=n;
	for(i=1;i<=n;i++){
		cin>>x;
		sum[i]=sum[i-1]+x;
		if(ans<sum[i]-q[head])ans=sum[i]-q[head];
		while(sum[i]<=q[rear]&&rear>0)rear--;
		q[++rear]=sum[i];
		num[rear]=i;
		while(num[head]+m<=i)head++;
	}
	cout<<ans<<endl;
//	for(i=head;i<=rear;i++)cout<<q[i]<<" ";cout<<endl;
//	for(i=1;i<=n;i++)cout<<num[i]<<" ";cout<<endl;
//	for(i=1;i<=n;i++)cout<<sum[i]<<" ";cout<<endl;
	return 0;
}