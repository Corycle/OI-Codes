#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
using namespace std;
int dzh(int x)
{	if(x==0||x==1)return 0;
	for(int i=2;i<x;i++)
	if(x%i==0)return 0;
	return 1;}
int main(){
	char a[101];cin>>a;
	int b[27],c=strlen(a)-1,i,j,max=0,min=110;
	memset(b,0,sizeof(b));
	for(i=0;i<=c;i++)b[a[i]-96]++;
	for(i=1;i<=26;i++)
	{	if(b[i]==0)continue;
		else if(max<b[i])max=b[i];
		else if(min>b[i])min=b[i];}
	if(dzh(max-min)==0)cout<<"No Answer"<<endl<<0;
	else cout<<"Lucky Word"<<endl<<max-min;
	return 0;
}
