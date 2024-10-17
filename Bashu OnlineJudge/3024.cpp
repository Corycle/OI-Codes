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
//queue<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int a[1000005],t,h[1000005],v[1000005],f[1000005],n,ans;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,p;
	cin>>n;
	for(i=1;i<=n;i++)cin>>h[i]>>v[i];
	for(i=1;i<=n;i++)f[i]=0;
	t=0;
	for(i=1;i<=n;i++){
		while(t&&(h[i]>=h[a[t]]))t--;
		if(t)f[a[t]]+=v[i];
		t++;
		a[t]=i;
	}
	t=0;
	for(i=n;i>=1;i--){
		while(t&&(h[i]>=h[a[t]]))t--;
		if(t!=0)f[a[t]]+=v[i];
		t++;
		a[t]=i;
	}
	ans=0;
	for(i=1;i<=n;i++)ans=max(f[i],ans);
	cout<<ans;
	return 0;
}
