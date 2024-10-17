#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
struct tom{
	int x,y,z;
}a[30005];
using namespace std;
int n,i,j,k,l,f[10000005];
bool cmp(tom o,tom p){
	return o.y<=p.y;
}
int main(){
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y>>a[i].z;
		l=max(l,a[i].y);
	}
	sort(a+1,a+n+1,cmp);
	for(i=1;i<=n;i++){
		for(j=a[i].y;j<=l;j++){
			f[j]=max(f[j-1],f[j]);
			if(j==a[i].y)f[a[i].y]=max(f[a[i].x]+a[i].z,f[a[i].y]);
		}
	}
	cout<<f[l];
	return 0;
}