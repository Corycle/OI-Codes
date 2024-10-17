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
const int Inv2=499122177;
const int Mod=998244353;
const int N=(1<<18)+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Sta;
int f[N],num[N],flag[N];
struct Edge{int x,y;}E[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Sta=(1<<n)-1;f[0]=1;
	for(int S=1;S<=Sta;S++)num[S]=num[S>>1]+(S&1);
	for(int i=1;i<=m;i++){E[i].x=read()-1;E[i].y=read()-1;}
	for(int S=1;S<=Sta;S++)for(int i=1;i<=m;i++)if(((S>>E[i].x)&1)&&((S>>E[i].y)&1))flag[S]=1;
	for(int S=1;S<=Sta;S++)for(int T=S;T;T=(T-1)&S)if(!flag[T])f[S]=(f[S]+1ll*f[S^T]*(num[T]&1?1:Mod-1))%Mod;
	printf("%lld",1ll*f[Sta]*Inv2%Mod*m%Mod);
	return 0;
}