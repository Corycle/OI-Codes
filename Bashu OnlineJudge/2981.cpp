#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
//struct _{};
using namespace std;
int n,i,j,k,l,top,f[200005];
int main(){
//  freopen("_.in","r",stdin):
//  freopen("_.out","w",stdout);
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>k;
		if(k==0){
			cin>>l;
			top++;
			f[top]=max(l,f[top-1]);
		}
		if(k==1&&top!=0){
			top--;
			f[top+1]=0;
		}
		if(k==2){
			cout<<f[top]<<endl;
		}
	}
	return 0;
}
