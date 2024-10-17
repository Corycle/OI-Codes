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
const int N=16005;
const int M=20005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tp,cnt,tot,scc;
int h[N],b[N],p[N],st[N],dfn[N],low[N],opp[N],vis[N];
struct edge{
	int to,next;
}d[M*2];
void edge_add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void Tarjan(int x){
	dfn[x]=low[x]=++tot;
	p[x]=1;st[++tp]=x;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(!dfn[y]){
			Tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(p[y]){
			low[x]=min(low[x],dfn[y]);
		}
	}
	if(dfn[x]==low[x]){
		int k=0;
		scc++;
		do{
			k=st[tp--];
			p[k]=0;
			b[k]=scc;
		}while(k!=x);
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int fx,fy;
		int x=read(),y=read();
		if(x&1)fx=x+1;else fx=x-1;
		if(y&1)fy=y+1;else fy=y-1;
		edge_add(x,fy);
		edge_add(y,fx);
	}
	for(int i=1;i<=n*2;i++){
		if(!dfn[i])Tarjan(i);
	}
	for(int i=1;i<=n;i++){
		if(b[i*2]==b[i*2-1]){
			printf("NIE");
			return 0;
		}
	}
	for(int i=1;i<=n*2;i++){
		if(i&1)opp[b[i]]=b[i+1];
		else opp[b[i]]=b[i-1];
	}
	for(int i=1;i<=scc;i++){
		if(!vis[i])vis[opp[i]]=1;
	}
	for(int i=1;i<=n*2;i++){
		if(!vis[b[i]])printf("%d\n",i);
	}
	return 0;
}