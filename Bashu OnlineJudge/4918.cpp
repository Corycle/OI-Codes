#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include<stack>
#include<queue>
#include<map>
using namespace std;
int n,m,a[15005],b[15005],c[15005],d[15005],w[40005],h[40005],x,s;
int main(){
	int i,j;
	scanf("%d%d",&n,&m);  
	for(i=1;i<=m;i++){  
		scanf("%d",&h[i]);  
		w[h[i]]++;  
	}  
	for(i=1;9*i<n;i++){  
		x=9*i+1;s=0;
		for(j=9*i+2;j<=n;j++){  
			s+=w[j-x]*w[j-x+2*i];  
			d[j]+=s*w[j-i];
			c[j-i]+=s*w[j];  
		}  
		s=0;  
		for(j=n-x;j>=1;j--){  
			s+=w[j+x]*w[j+x-i];
			a[j]+=s*w[j+2*i];
			b[j+2*i]+=s*w[j];
		}  
	}  
	for(i=1;i<=m;i++)  
		printf("%d %d %d %d\n",a[h[i]],b[h[i]],c[h[i]],d[h[i]]);
	return 0; 
}