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
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Q,top,tot,num,scc,cnt=1;
int h[N],b[N],st[N],prt[N],dfn[N],low[N],vis[N];
struct edge{int to,next;}d[N];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void Tarjan(int x,int pre){
	dfn[x]=low[x]=++tot;st[++top]=x;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(i==(pre^1))continue;
		if(!dfn[y]){
			Tarjan(y,i);
			low[x]=min(low[x],low[y]);
			if(low[y]>dfn[x])vis[i]=vis[i^1]=1;
			if(low[y]>=dfn[x]){
				int k=0;prt[++num]=x;
				do{k=st[top--];prt[k]=num;}while(k!=y);
			}
		}
		else low[x]=min(low[x],dfn[y]);
	}
}
void DFS(int x){
	b[x]=scc;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(b[y]||vis[i])continue;
		DFS(y);
	}
}
bool Check1(int x,int y){return (prt[x]&&prt[x]==prt[y])||prt[prt[x]]==y||prt[prt[y]]==x||x==y;}
bool Check2(int x,int y){return b[x]==b[y];}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Q=read();num=n;
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		if(x==y)continue;
		Add(x,y);Add(y,x);
	}
	for(int i=1;i<=n;i++)if(!dfn[i])Tarjan(i,0);
	for(int i=1;i<=n;i++)if(!b[i]){scc++;DFS(i);}
	while(Q--){
		int op=read(),x=read(),y=read();
		if(op==1)puts(Check1(x,y)?"yes":"no");
		if(op==2)puts(Check2(x,y)?"yes":"no");
	}
	return 0;
}