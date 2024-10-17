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
int n,q[1005],a[1005],b[1005],f[1005],x=1,y=1;
void haha(){
	int i,j,k,l;
	while(x<=y){
		for(i=1;i<=n;i++){
			if(b[i]==q[x]&&f[a[i]]==0){
				y++;
				q[y]=a[i];
				cout<<q[y]<<" ";
			}
		}
		x++;
	}
	
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k,l;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		if(b[i]==0)k=a[i];
	}
	q[1]=k;
	cout<<k<<" ";
	haha();
	return 0;
}