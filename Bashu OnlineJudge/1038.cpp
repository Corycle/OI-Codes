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
struct _{
	string num,name;
	int len;
}a[1005];
//stack<_>_;
//queue<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int n;
bool cmp(_ x,_ y){
	if(x.len!=y.len)return x.len>y.len;
	int i,j,k;
	for(i=0;i<=x.len;i++){
		if(x.num[i]!=y.num[i])return x.num[i]>y.num[i];
	}
	return x.name<y.name;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a[i].name>>a[i].num;
		a[i].len=a[i].num.length()-1;
	}
	sort(a+1,a+n+1,cmp);
	for(i=1;i<=n;i++)cout<<a[i].name<<endl;
	return 0;
}
