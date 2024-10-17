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
int n,m,i,j,k,l;
int a[2005],b[2005],s;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	cin>>n>>m;
	for(i=1;i<=n;i++){
		cin>>a[i];
	}
	for(i=1;i<=m;i++){
		cin>>b[i];
	}
//	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	
	for(i=1;i<=n;i++){
		for(j=m;j>=1;j--){
			if(a[i]>b[j]&&b[j]!=0){
				b[j]=0;
				s++;
				break;
			}
		}
	}
	cout<<m-s;
	return 0;
}