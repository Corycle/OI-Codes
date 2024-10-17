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
const int Mod=998244353;
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
int n,m,f[N],g[N],h[N],fa[N];
int mod(int x){return x>=Mod?x-Mod:x;}
void DFS(int x){
	if(G[x].empty()){g[x]=1;return;}
	h[x]=1;
	for(auto y:G[x]){
		DFS(y);
		g[x]=mod(1ll*f[x]*mod(g[y]+f[y])%Mod+1ll*g[x]*mod(mod(f[y]+g[y])+mod(g[y]+h[y]))%Mod);
		f[x]=mod(1ll*f[x]*mod(g[y]+h[y])%Mod+1ll*h[x]*mod(f[y]+g[y])%Mod);
		h[x]=1ll*h[x]*mod(g[y]+h[y])%Mod;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=2;i<=n;i++)G[fa[i]=read()].push_back(i);
	DFS(1);
	printf("%d",mod(g[1]+h[1]));
	return 0;
}
