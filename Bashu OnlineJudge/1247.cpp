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
int f[105],s[105],n,m,p,maxx;
int main(){
	int i,j,k;
	cin>>n>>m;
	for(i=1;i<=n;i++)f[i]=i;
	for(i=1;i<=m;i++){
		cin>>j>>k;
		while(f[j]!=j)j=f[j];
		while(f[k]!=k)k=f[k];
		if(f[j]!=f[k])f[k]=f[j];
	}
	for(i=1;i<=n;i++){
		j=i;
		while(f[j]!=j)j=f[j];
		if(s[j]==0)p++;
		s[j]++;
		maxx=max(maxx,s[j]);
	}
	cout<<p<<" "<<maxx;
	return 0;
}