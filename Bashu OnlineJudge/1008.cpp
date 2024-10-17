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
int a,b,maxx;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k=0;
	for(i=1;i<=7;i++){
		cin>>a>>b;
		if(maxx<a+b&&a+b>0){
			k=i;
			maxx=a+b;
		}
	}
	cout<<k;
	return 0;
}