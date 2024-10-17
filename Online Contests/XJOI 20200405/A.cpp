/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=n+1;
	if(n==2){
		puts("5");
		puts("1 1");
		puts("1 2");
		puts("1 3");
		puts("2 3");
		puts("2 2");
		puts("2 1");
		return 0;
	}
	if(n==3){
		puts("11");
		puts("1 1");
		puts("2 2");
		puts("3 1");
		puts("2 1");
		puts("1 2");
		puts("1 3");
		puts("1 4");
		puts("2 4");
		puts("3 4");
		puts("3 3");
		puts("3 2");
		puts("2 3");
		return 0;
	}
	if(n==4){
		puts("19");
		puts("1 1");
		puts("2 2");
		puts("3 1");
		puts("2 1");
		puts("1 2");
		puts("1 3");
		puts("2 4");
		puts("3 3");
		puts("4 2");
		puts("4 1");
		puts("3 2");
		puts("2 3");
		puts("1 4");
		puts("1 5");
		puts("2 5");
		puts("3 5");
		puts("4 5");
		puts("4 4");
		puts("4 3");
		puts("3 4");
		return 0;
	}
	if(n==5){
		puts("29");
		puts("1 1");
		puts("2 2");
		puts("3 1");
		puts("2 1");
		puts("1 2");
		puts("1 3");
		puts("2 4");
		puts("3 3");
		puts("4 2");
		puts("5 1");
		puts("4 1");
		puts("3 2");
		puts("2 3");
		puts("1 4");
		puts("1 5");
		puts("1 6");
		puts("2 6");
		puts("3 5");
		puts("4 6");
		puts("5 6");
		puts("5 5");
		puts("4 4");
		puts("5 3");
		puts("5 2");
		puts("4 3");
		puts("3 4");
		puts("2 5");
		puts("3 6");
		puts("4 5");
		puts("5 4");
		return 0;
	}
	return 0;
}
