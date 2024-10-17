#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
using namespace std;
int n,a[5005],p[5005],t[5005],f[5005],maxx,ans,i,j,k;
int main(){
	cin>>n;
	for(i=1;i<=n;i++)cin>>a[i];
	a[n+1]=-1;n++;
	for(i=1;i<=n;i++){
		f[i]=t[i]=1;
		p[i]=0;
		for(j=i+1;j<=n;j++){
			if(a[i]==a[j]){
				p[i]=j;break;
			}
		}
	}
	for(i=2;i<=n;i++){
		for(j=1;j<i;j++){
			if(a[i]<a[j]&&(p[j]==0||p[j]>i)){
				if(f[j]+1>f[i])t[i]=t[j],f[i]=f[j]+1;
				else if(f[j]+1==f[i])t[i]+=t[j];
				t[i]=t[i]%10000;
			}
		}
	}
	cout<<f[n]-1<<" "<<t[n];
	return 0;
}