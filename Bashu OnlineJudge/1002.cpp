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
int m[501],rr[75],sum;
int main(){
	int n,r;
	cin>>n>>r;
	for(int i=0;i<n;i++)cin>>m[i];
	if(n<=r){
		for(int i=0;i<n;i++)
		sum+=m[i];
	}
	else{
		sort(m,m+n);
		for(int i=0;i<r;i++)rr[i]=m[i];
		int cur=r; 
		while(cur<=n)
		{
			int flag=1;
			while(flag){
				for(int i=0;i<r;i++)rr[i]--;
				sum+=r+n-cur;
				for(int i=0;i<r;i++)
					if(rr[i]==0)flag=0;
			}
			for(int i=0;i<r;i++){
				if(rr[i]==0){
					rr[i]=m[cur];
					cur++;
				}
			}
		}
		for(int i=0;i<r;i++)sum+=rr[i];
	}
	cout<<sum;	
	return 0;
}