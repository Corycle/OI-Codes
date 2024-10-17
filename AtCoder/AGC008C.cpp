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
ll a1,a2,a3,a4,a5,a6,a7;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	a1=read();a2=read();a3=read();a4=read();a5=read();a6=read();a7=read();
	ll Ans=a2+(a1/2)*2+(a4/2)*2+(a5/2)*2+(a1&a4&a5&1)*3;
	Ans=max(Ans,a2+((a1-1)/2)*2+((a4-1)/2)*2+((a5-1)/2)*2+(a1>0&&a4>0&&a5>0)*3);
	printf("%lld\n",Ans);
	return 0;
}
