#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
using namespace std;
int n,m,f[10005],a[205],i,j,k,l;
int main(){
	memset(f,10005,sizeof(f));
	f[0]=0;
	cin>>n>>m;
	for(i=1;i<=n;i++)cin>>a[i];
	for(i=1;i<=m;i++){
		for(j=1;j<=n;j++){
			if(i>=a[j])f[i]=min(f[i],f[i-a[j]]+1);
		}
	}
	for(i=1;i<=m;i++)
		if(f[i]!=0)cout<<f[i]<<endl;
		else cout<<-1<<endl;
	return 0;
}