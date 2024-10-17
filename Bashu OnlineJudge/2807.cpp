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
queue<int>dzh;
int n,a[1005],ans,m;
int main(){
	int i,j,k;
	cin>>n>>m;
	for(i=1;i<=m;i++){
		cin>>k;
		if(a[k]==0){
			a[k]=1;
			dzh.push(k);
			if(dzh.size()>n){
				j=dzh.front();
				a[j]=0;
				dzh.pop();
			}
			ans++;
		}
	}
	cout<<ans;
	return 0;
}