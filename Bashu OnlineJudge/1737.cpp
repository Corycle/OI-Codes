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
priority_queue<int >q;
priority_queue<int,vector<int>,greater<int> >q1;
int n;
int x;
int a;
int ans;
int main(){
cin>>n;
for(int i=1;i<=n;i++){
	cin>>x;
	for(int j=1;j<=x;j++){
		cin>>a;
		q.push(a);
		q1.push(a);
	}
		ans+=q.top()-q1.top();
		q.pop();
		q1.pop();
}	
	cout<<ans;
}
