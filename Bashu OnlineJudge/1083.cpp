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
int f[5005],n,m,p;
int main(){
	int i,j,k,s1,s2;
	cin>>n>>m>>p;
	for(i=1;i<=n;i++)f[i]=i;
	for(i=1;i<=m;i++){
		cin>>j>>k;
		s1=j,s2=k;
		while(f[s1]!=s1)s1=f[s1];
		while(f[s2]!=s2)s2=f[s2];
		f[s1]=s2;
	}
	for(i=1;i<=p;i++){
		cin>>j>>k;
		s1=j,s2=k;
		while(f[s1]!=s1)s1=f[s1];
		while(f[s2]!=s2)s2=f[s2];
		if(s1==s2)cout<<"Yes"<<endl;
		else cout<<"No"<<endl;
	}
	return 0;
}