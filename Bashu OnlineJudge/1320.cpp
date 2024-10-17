#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
using namespace std;
int a[500005],s[500005],d[500005],n,i,j,k,l,top=1;
int main(){
	cin>>n;
	s[1]=1;
	for(i=n;i>=1;i--)cin>>a[i];
	for(i=2;i<=n;i++){
		if(a[s[top]]<=a[i]){
			top++;
			s[top]=i;
			
		}
		else{
			while(a[i]<a[s[top]]&&top!=0){
				d[s[top]]=i;
				top--;
			}
			s[top+1]=i;
			top++;
		}
	}
	d[n]=0;
	for(i=n;i>=1;i--)cout<<a[d[i]]<<" ";
    return 0;
}