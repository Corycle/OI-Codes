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
int w,n,a[30005];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	cin>>w>>n;
	int i,j,k=0;
	for(i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	i=1;j=n;
	while(i<=j){
		if(a[i]+a[j]<=w){
			i++;
			j--;
			k++;
		}
		else{
			k++;
			j--;
		}
	}
	cout<<k;
	return 0;
}