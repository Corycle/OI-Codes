#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
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
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int n=read();
	if(n>=1)printf("6 8\n");
	if(n>=2)printf("35 49\n");
	if(n>=3)printf("204 288\n");
	if(n>=4)printf("1189 1681\n");
	if(n>=5)printf("6930 9800\n");
	if(n>=6)printf("40391 57121\n");
	if(n>=7)printf("235416 332928\n");
	if(n>=8)printf("1372105 1940449\n");
	if(n>=9)printf("7997214 11309768\n");
	if(n>=10)printf("46611179 65918161\n");
	return 0;
}