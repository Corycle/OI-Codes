#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
using namespace std;
int main(){
	char a[1000000];
	memset(a,0,sizeof(a));
	cin.getline(a,1000000);
	int s=0,i;
	for(i=0;i<=999999;i++)
	{	if((a[i]<'A'||(a[i]>'Z'&&a[i]<'a')||a[i]>'z')&&((a[i-1]>='A'&&a[i-1]<='Z')||(a[i-1]>='a'&&a[i-1]<='z')))
		s++;}
	cout<<s;
	return 0;
}
