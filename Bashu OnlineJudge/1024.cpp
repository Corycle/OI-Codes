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
int s,p;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i;
	cin>>p;
	for(i=10000;i<=30000;i++){
		if(i/100%p==0&&i/10%1000%p==0&&i%1000%p==0){
			s++;
			cout<<i<<endl;
		}
	}
	if(s==0)cout<<"No";
	return 0;
}