#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
//struct _(){};
using namespace std;
int main(){
//  freopen("_.in","r",stdin):
//  freopen("_.out","w",stdout);
	int a,d,v=0;char b[100];long long s=0;
	memset(b,0,sizeof(b));
	cin>>a>>b;
	cout<<"(";
	d=strlen(b)-1;
	for(int i=0;i<=d;i++)cout<<b[i];
	cout<<")"<<a<<"=(";
	for(d;d>=0;d--)
	{	if(b[d]>57)b[d]-=7;
		s+=(b[d]-48)*pow(a,v);
		v++;}
	cout<<s<<")10";
	return 0;
}
