#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
#include<stack>
using namespace std;
stack<int>dzh;
int n,i,j,k,l,ans;
int main(){
	cin>>n;
	ans=n;
	for(i=1;i<=n;i++){
		cin>>k;
		while(dzh.size()!=0&&dzh.top()>=k){
			if(dzh.top()==k){
				ans--;
				dzh.pop();
			}
			else dzh.pop();
		}
		dzh.push(k);
	}
	cout<<ans;
    return 0;
}