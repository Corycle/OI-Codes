#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
using namespace std;
int main(){
	int n,b,a[10001],m[10001]={0},i,j,s=0,v=0,f=0;
	cin>>n>>b;		//n个人，b个水龙头
	b=min(n,b);
	for(i=1;i<=n;i++)
		cin>>a[i];
	while(1)
	{	v=101;
		for(i=1;i<=b;i++)
			if(m[i]==0&&f<n){
				f++;
				m[i]=a[f];
			}
		for(i=1;i<=b;i++)
			if(v>m[i]&&m[i]!=0){
				j=i;v=m[i];
			}
		for(i=1;i<=b;i++)
			if(m[i]!=0)m[i]-=v;
		s+=v;
		if(f==n)
		for(i=1;i<=b;i++){
				if(m[i]!=0)break;
				if(i==b){
					cout<<s;
					return 0;
			}
		}
	}
	return 0;
}