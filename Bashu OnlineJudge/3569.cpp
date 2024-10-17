#include<iostream>
#include<queue>
using namespace std;
int k,n,a[500005],sum,ans;
queue<int> q;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		q.push(a[i]);
		sum+=a[i];
		while(sum>k){
			int x=q.front();
			q.pop();
			sum-=x;
		}
		if(sum==k) ans++;
	}
	cout<<ans;
}