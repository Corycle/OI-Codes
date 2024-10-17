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
const int maxx=256*256;
int n,a[15],f[maxx];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k,l=0;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	if(a[1]==1){
		cout<<0;
		return 0;
	}
	f[0]=1;
	for(i=1;i<=maxx;i++){
		for(j=1;j<=n;j++){
			if(i>=a[j]&&f[i-a[j]]==1)f[i]=1;
		}
	} 
	for(i=maxx;i>=1;i--){
		if(f[i]==0){
			if(i>255*256-255-256)cout<<0;
			else cout<<i;
			return 0;
		}
	}
	return 0;
}