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
#define inf 0x3f3f3f3f
#define ll long long 
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m;
int main(){
//  freopen(".in","r",stdin);
//  freopen(".out","w",stdout);
	n=read();m=read();
	if(n/m%2==1)printf("YES");
	else printf("NO");
	return 0;
}
