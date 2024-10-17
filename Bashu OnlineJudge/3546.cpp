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
const int N=10005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,top,tot,scc,cnt=1;
int h[N],b[N],st[N],rd[N],vis[N],dfn[N],low[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
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
		do{
			k=st[top--];
			b[k]=scc;
			vis[k]=0;
		}while(x!=k);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	for(int i=1;i<=n;i++)if(!dfn[i])Tarjan(i,0);
	for(int x=1;x<=n;x++){
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(b[x]!=b[y])rd[b[y]]++;
		}
	}
	int Ans=0;
	for(int i=1;i<=scc;i++)Ans+=(rd[i]==1);
	printf("%d",(Ans+1)/2);
	return 0;
}