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
#define uint unsigned int
using namespace std;
const int inf=0x3f3f3f3f;
const int Maxn=(1<<23)+5;
const int N=50;
const int M=24;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N][N];
uint f[Maxn],g[Maxn];
int h[Maxn],num[Maxn];
int lowbit(int x){return x&(-x);}
int n,m,tot,Sta,a[N][N],id[N],fa[N],sum[N];
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
void Union(int x,int y){x=Find(x);y=Find(y);if(x!=y){fa[x]=y;sum[y]+=sum[x];}}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)scanf("%s",s[i]+1);
	for(int i=1;i<=n;i++){fa[i]=i;sum[i]=1;}
	for(int i=1;i<=n;i++)for(int j=1;j<i;j++)if(s[i][j]=='A')Union(i,j);
	for(int i=1;i<=n;i++)for(int j=1;j<i;j++)if(s[i][j]=='X'&&Find(i)==Find(j)){puts("-1");return 0;}
	for(int i=1;i<=n;i++)if(!id[Find(i)]&&sum[Find(i)]>=2)id[Find(i)]=++tot;
	if(!tot){printf("%d\n",n-1);return 0;}
	Sta=(1<<tot)-1;
	for(int i=1;i<=n;i++)for(int j=1;j<i;j++)if(s[i][j]=='X'){int x=id[Find(i)],y=id[Find(j)];a[x][y]=a[y][x]=1;}
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(a[i][j])h[1<<(i-1)]|=(1<<(j-1));
	f[0]=1;
	for(int S=1;S<=Sta;S++){
		g[S]=1;
		num[S]=num[S>>1]+(S&1);
		f[S]=f[S^lowbit(S)]+f[(S^lowbit(S))^(S&h[lowbit(S)])];
	}
	for(int S=1;S<=Sta;S++)f[S]--;
	for(int k=1;k<=tot;k++){
		uint ans=0;
		for(int S=1;S<=Sta;S++){
			g[S]*=f[S];
			ans+=(num[Sta^S]&1?-1:1)*g[S];
		}
		if(ans){printf("%d",n+k-1);return 0;}
	}
	return 0;
}
