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
const int N=1005;
int n,m;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	if(c=='w')s=s+1;
	if(c=='h')s=s+1+n;
	return s*f;
}
int tp,cnt,tot,scc;
int h[N],p[N],b[N],st[N];
int dfn[N],low[N],vis[N],opp[N];
struct edge{
	int to,next;
}d[N*N];
void Add(int x,int y){
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
void Print(int x){
	if(x>n*2)x-=n*2;
	printf("%d%c ",(x-1)%n,(x<=n?'w':'h'));
}
void Init(){
	cnt=tot=scc=tp=0;
	memset(h,0,sizeof(h));
	memset(d,0,sizeof(d));
	memset(p,0,sizeof(p));
	memset(b,0,sizeof(b));
	memset(st,0,sizeof(st));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	memset(vis,0,sizeof(vis));
	memset(opp,0,sizeof(opp));
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	Add(1+n*2,1+n*0);
	Add(1+n*1,1+n*3);
	for(int i=2;i<=n;i++){
		Add(i+n*0,i+n*3);
		Add(i+n*1,i+n*2);
		Add(i+n*2,i+n*1);
		Add(i+n*3,i+n*0);
	}
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		Add(x+n*2,y);Add(y+n*2,x);
	}
	for(int i=1;i<=n*4;i++){
		if(!dfn[i])Tarjan(i);
	}
	int flag=0;
	for(int i=1;i<=n*2;i++){
		opp[b[i]]=b[i+n*2];
		opp[b[i+n*2]]=b[i];
		if(b[i]==b[i+n*2]){
			printf("bad luck\n");
			return 0;
		}
	}
	for(int i=1;i<=scc;i++){
		if(!vis[i])vis[opp[i]]=1;
	}
	for(int i=2;i<=n*2;i++)if(!vis[b[i]])Print(i);
	printf("\n");
	return 0;
}