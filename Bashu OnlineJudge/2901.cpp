#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
using namespace std;
int a[100005],s[100005],d[100005],n,i,j,k,l,top=1;
int main(){
	cin>>n;
	s[1]=1;
	for(i=1;i<=n;i++)cin>>a[i];
	for(i=2;i<=n;i++){
		if(a[s[top]]>=a[i]){
			top++;
			s[top]=i;
			
		}
		else{
			while(a[i]>a[s[top]]&&top!=0){
				d[s[top]]=i;
				top--;
			}
			s[top+1]=i;
			top++;
		}
	}
	
	for(i=1;i<=n;i++)cout<<d[i]<<" ";
    return 0;
}