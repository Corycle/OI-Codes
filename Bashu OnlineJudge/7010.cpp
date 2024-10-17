/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<cstring>
#include<complex>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#define ll long long
#define ull unsigned ll
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e6+5;
const int M=65;
ull read(){
	ull s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,c,K,tot,num,a[M],b[M];
int main(){
//	freopen("zoo.in","r",stdin);
//	freopen("zoo.out","w",stdout);
	n=read();m=read();c=read();K=read();
	for(int i=1;i<=n;i++){ull x=read();for(int j=0;j<=63;j++)if((x>>j)&1)a[j]=1;}
	for(int i=1;i<=m;i++){int x=read(),y=read();if(!a[x])b[x]=-1;}
	for(int i=0;i<K;i++)num+=(b[i]>=0);
	if(!n&&num==64){puts("18446744073709551616");return 0;}
	ull ans=1;ans<<=num;if(num==64)ans=0;ans-=n;
	printf("%llu\n",ans);
	return 0;
}