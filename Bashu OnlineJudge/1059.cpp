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
int n;
long long s;
priority_queue<int,vector<int>,greater<int> >q;
int main(){	
	int i,j,k;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>j;
		q.push(j);
	}
	for(i=1;i<n;i++){
		j=q.top();
		q.pop();
		k=q.top();
		q.pop();
		s+=j+k;
		q.push(j+k);
	}
	cout<<s;
	return 0;
}