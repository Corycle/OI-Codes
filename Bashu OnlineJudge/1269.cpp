#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
using namespace std;
int i=1,j,k,x,n,maxx,m,a[4005],b[4005],h[4005],s; 
int main(){
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a[i];
		maxx=x=0;
		for(j=1;j<i;j++){
			if(a[j]>=a[i]&&b[j]>maxx)
			maxx=b[j];
		}
		b[i]=maxx+1;
		if(b[i]>m)m=b[i];
		for(k=1;k<=s;k++){
			if((h[k]>=a[i]&&x==0)||h[k]<h[x])
			x=k;
		}
		if(x==0){
			s++;
			x=s;
		}
		h[x]=a[i];
	}
	cout<<m<<endl<<s;
	return 0;
}