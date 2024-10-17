#include<iostream>
using namespace std;
int f(int n,int q)
{
	int k=n/2;
	if(n==1)return 1;
	if(q<=k)return n-k+f(k,k+1-q);
	if(q>k)return f(n-k,n+1-q);
}
int main()
{
	int n,q;
	cin>>n>>q;
	cout<<f(n,q)<<endl;
}