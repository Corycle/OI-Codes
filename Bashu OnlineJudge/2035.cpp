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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,fa[N],son[N],Max[N];
ll DP[N*10],*f[N],*g[N],*pos=DP,Ans;
vector<int>G[N];
void DFS1(int x){
	for(auto y:G[x]){
		if(y==fa[x])continue;
		fa[y]=x;DFS1(y);
		if(Max[son[x]]<Max[y])son[x]=y;
	}
	Max[x]=Max[son[x]]+1;
}
void DFS2(int x){
	if(son[x]){
		f[son[x]]=f[x]+1;
		g[son[x]]=g[x]-1;
		DFS2(son[x]);
	}
	f[x][0]=1;Ans+=g[x][0];
	for(auto y:G[x]){
		if(y==fa[x]||y==son[x])continue;
		f[y]=pos;pos+=Max[y]<<1;
		g[y]=pos;pos+=Max[y]<<1;
		DFS2(y);
		for(int i=0;i<=Max[y];i++){
			if(i)Ans+=f[x][i-1]*g[y][i];
			Ans+=g[x][i+1]*f[y][i];
		}
		for(int i=0;i<=Max[y];i++){
			if(i)g[x][i-1]+=g[y][i];
			g[x][i+1]+=f[x][i+1]*f[y][i];
			f[x][i+1]+=f[y][i];
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	while(1){
		n=read();
		if(!n)break;
		for(int i=1;i<n;i++){
			int x=read(),y=read();
			G[x].push_back(y);
			G[y].push_back(x);
		}
		DFS1(1);
		f[1]=pos;pos+=Max[1]<<1;
		g[1]=pos;pos+=Max[1]<<1;
		DFS2(1);
		printf("%lld\n",Ans);
		Ans=0;
		for(int i=1;i<=n;i++){
			G[i].clear();
			fa[i]=son[i]=Max[i]=0;
		}
	}
	return 0;
}