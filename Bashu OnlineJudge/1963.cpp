#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
using namespace std; 
int f[501],s1[2001],s2[2001],w1[2001],w2[2001],m2[2001];
int v,n,n1,n2,m,w,s,i,j,k;
int main(){;
	cin>>n>>v;
	for(i=1;i<=n;i++){
		cin>>m>>w>>s; 
    	if(m*w>=v){
			n1++; 
			w1[n1]=w;
			s1[n1]=s;
		} 
    	if(m*w<v){
			n2++;
			w2[n2]=w;
			s2[n2]=s;
			m2[n2]=m;
		}
	}
	for(i=1;i<=n2;i++){
		for(k=1;k<=m2[i];k++){
			for(j=v;j>=w2[i];j--){
				if(f[j]<f[j-w2[i]]+s2[i])
				f[j]=f[j-w2[i]]+s2[i];
			}
		}
	}
	for(i=1;i<=n1;i++){
		for(j=w1[i];j<=v;j++){
			if(f[j]<f[j-w1[i]]+s1[i])
			f[j]=f[j-w1[i]]+s1[i];
		}
	}
	cout<<f[v];
	return 0;
}