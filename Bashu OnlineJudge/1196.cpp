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
struct hahaha{
	int l,r,tree;
}f[1005];
using namespace std;
//stack<_>_;
//queue<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
void zhao(int a){
	if(f[a].l!=0)zhao(f[a].l);
	cout<<f[a].tree<<endl;
	if(f[a].r!=0)zhao(f[a].r);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,n;
	cin>>n;
	for(i=1;i<=n;i++)cin>>f[i].tree>>f[i].l>>f[i].r;
	zhao(1);
	return 0;
}