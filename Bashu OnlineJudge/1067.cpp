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
//queue<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int n,m,p,q,a[50],f[50][50],s[50][50];
int DP(int l,int r){
	int i,j,k;
	if(l==r)return a[l];
	if(l==r-1)return a[l]+a[r];
	if(f[l][r])return f[l][r];
	for(i=l+1;i<=r;i++){
		if(f[l][r]<DP(l,i-1)*DP(i+1,r)+a[i]){
			f[l][r]=DP(l,i-1)*DP(i+1,r)+a[i];
			s[l][r]=i;
		}
	}
	return f[l][r];
}
void tree(int l,int r){
	int i,j,k;
	if(l==r){
		cout<<l<<" ";
		return;
	}
	if(l==r-1){
		cout<<l<<" "<<r<<" ";
		return;	
	}
	cout<<s[l][r]<<" ";
	if(l<=s[l][r]-1)tree(l,s[l][r]-1);
	if(s[l][r]+1<=r)tree(s[l][r]+1,r);
}
int main(){
	int i,j,k,l;
	cin>>n;
	for(i=1;i<=n;i++)cin>>a[i];
	cout<<DP(1,n)<<endl;
	tree(1,n);
	return 0;
}