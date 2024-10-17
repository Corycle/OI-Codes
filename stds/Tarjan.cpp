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
const int N=400005;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,top,tot,scc,cnt=1;
int h[N],H[N],b[N],fa[N],st[N],dep[N],vis[N],dfn[N],low[N],p[N][M];
struct edge{int to,next;}d[N*2],e[N*2];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void Tarjan(int x,int pre){
	dfn[x]=low[x]=++tot;
	st[++top]=x;vis[x]=1;
	for(int i=h[x];i;i=d[i].next){
		if(i==(pre^1))continue;
		int y=d[i].to;
		if(!dfn[y]){
			Tarjan(y,i);
			low[x]=min(low[x],low[y]);
		}
		else if(vis[y])low[x]=min(low[x],dfn[y]);
	}
	if(dfn[x]==low[x]){
		int k=0;scc++;
		do{k=st[top--];b[k]=scc;vis[k]=0;}while(x!=k);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	
	return 0;
}
