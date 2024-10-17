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
int n,m,f[30005],p[30005],maxx;
int main(){
	cin>>n>>m;
	int i,j,k,s1,s2;
	for(i=1;i<=n;i++){
		f[i]=i;
	}
	for(i=1;i<=m;i++){
		cin>>j>>k;
		s1=j;s2=k;
		while(s1!=f[s1])s1=f[s1];
		while(s2!=f[s2])s2=f[s2];
		f[min(s1,s2)]=max(s1,s2);
	}
	for(i=1;i<=n;i++){
		s1=i;
		while(s1!=f[s1])s1=f[s1];
		p[s1]++;
		maxx=max(maxx,p[s1]);
	}
	cout<<maxx;
	return 0;
}