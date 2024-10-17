#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
using namespace std;
char k[1005],c[1005],m[1005];
char ttt(char a,char b)
{	char m;
	if(b>='a'&&b-'a'+1<a)b+=26;
	else if(b<='Z'&&b-'A'+1<a)b+=26;
	m=b-a;if(m==96||m==64)m+=26;
	return m;}
int main(){
	memset(k,0,sizeof(k));
	memset(c,0,sizeof(c));
	memset(m,0,sizeof(m));
	cin>>k>>c;
	int a=strlen(k),b=strlen(c),i;
	for(i=0;i<a;i++)
	if(k[i]>='a'&&k[i]<='z')k[i]-='a';
	else if(k[i]<='Z'&&k[i]>='A')k[i]-='A';
	for(i=0;i<b;i++)
	{	if(i>=a)k[i]=k[i-a];
		m[i]=ttt(k[i],c[i]);
		cout<<m[i];}
	return 0;
}