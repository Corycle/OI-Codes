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
	int s,t,w;
}a[100005];
//stack<_>_;
//queue<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int n,m,num=1,g[1005];
bool cmp(_ x,_ y){
	return x.w<y.w;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k,l;
	cin>>n>>m;
	for(i=1;i<=n;i++)g[i]=i;
	for(i=1;i<=m;i++){
		cin>>a[i].s>>a[i].t>>a[i].w;
	}
	sort(a+1,a+m+1,cmp);
	for(i=1;i<=m;i++){
		j=a[i].s;k=a[i].t;l=a[i].w;
		while(j!=g[j])j=g[j];
		while(k!=g[k])k=g[k];
		if(j!=k){
			g[j]=k;
			num++;
			if(num==n){
				cout<<l;
				return 0;
			}
		}
	}
	cout<<-1;
	return 0;
}