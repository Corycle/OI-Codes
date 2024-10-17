#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
using namespace std;
int k,n,a[25],b[25],t[25],s=0;
int ppdd(){
	int tot=0,i;
	for(i=1;i<=k;i++)tot+=a[t[i]];
	if(tot==0||tot==1)return 0;
	for(i=2;i*i<=tot;i++)
	if(tot%i==0)return 0;
	return 1;
}
void search(int f){
	int i;
	if(f==k+1&&ppdd())s++;
	else{
		for(i=t[f-1];i<=n;i++)
		if(f==1&&i>(n-k+1))return ;
		else if(b[i]==0){
			t[f]=i;
			b[i]=1;
			search(f+1);
			b[i]=0;
		}
	}
}
int main(){
	int i;
	t[0]=1;
	cin>>n>>k;
	for(i=1;i<=n;i++)cin>>a[i];
	search(1);
	cout<<s;
	return 0;
}
