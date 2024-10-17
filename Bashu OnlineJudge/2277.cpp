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
//struct _{};
using namespace std;
//stack<_>_;
queue<int>a;
priority_queue<int>b;
//priority_queue<int,vector<int>,greater<int> >_;
int n,i,j,k,l,m,f;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	cin>>n>>m;m++;
	for(i=1;i<=n;i++){
		cin>>l;
		b.push(l);
		if(m==i)l*=10;
		f=max(f,l);
		a.push(l);
	}
	while(1){
		if(a.front()==f){
			if(f/10==b.top()){
				j++;
				cout<<j;
				return 0;
			}
			else{
				a.pop();
				a.push(f);
				continue;
			}
		}
		if(a.front()==b.top()){
			j++;
			a.pop();
			b.pop();
		}
		else{
			a.push(a.front());
			a.pop();
		}
	}
	return 0;
}
