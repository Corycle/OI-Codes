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

int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int a=read(),b=read();
	if(a>0){puts("Positive");return 0;}
	if(a<=0&&b>=0){puts("Zero");return 0;}
	if((b-a+1)&1){puts("Negative");return 0;}
	puts("Positive");
	return 0;
}
