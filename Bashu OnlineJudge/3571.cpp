#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
using namespace std;
int n,i,j,k,l,f[1005],a[1005];
int main(){
	cin>>n;
	for(i=1;i<=n;i++)cin>>a[i];
	f[a[1]]=1;
	for(i=1;i<=n;i++){
		if(abs(a[i]-a[i+1])!=1&&a[i]>a[i+1]){
			k=a[i];
			l=a[i+1];
			if(k>l)swap(k,l);
			for(k=k+1;k<l;k++)if(f[k]!=1){
				cout<<"NO";
				return 0;
			}
		}
		f[a[i]]=f[a[i+1]]=1;
	}
	cout<<"YES";
	return 0;
}