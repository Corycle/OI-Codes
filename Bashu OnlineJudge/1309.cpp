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
//stack<_>_;
//queue<int>q;
//priority_queue<_>f;
//priority_queue<_,vector<int>,greater<int> >f;
int a[205][205],n,m,c[205],r[205],ans[205],s,t,num;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	cin>>n;
	while(cin>>j>>k){
		r[k]++;
		a[j][k]=1;
	}
	while(num!=n){
		k=1;
		for(i=1;i<=n;i++){
			if(r[i]==0&&c[i]==0){
				k=0;
				c[i]=1;
				for(j=1;j<=n;j++){
					if(a[i][j]){
						r[j]--;
					}
				}
				num++;
				ans[num]=i;
			}
		}
		if(num<n&&k){
			cout<<"No answer";
			return 0;
		}
	}
	for(i=1;i<=n;i++){
		cout<<ans[i]<<" ";
	}
	return 0;
}