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
int n,a[100005];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a[i];
		a[0]++;
		k=a[0];
		while(k>1&&a[k]<a[k/2]){swap(a[k],a[k/2]);k=k/2;}
	}
	for(k=1;k<=n;k++){
		cout<<a[1]<<" ";
		a[1]=a[a[0]];
		a[0]--;
		i=1;
		while(i*2<=a[0]){
			if(i*2==a[0]||a[i*2]<a[i*2+1])j=i*2;else j=2*i+1;
			if(a[i]>a[j]){
				swap(a[i],a[j]);
				i=j;
			}
			else break;
		}
	}
	return 0;
}