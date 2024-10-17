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
const int N=5005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tp,cnt,tot,scc;
int h[N],p[N],b[N],st[N];
int dfn[N],low[N],vis[N],opp[N];
int key1[N],key2[N],door1[N],door2[N];
struct edge{
	int to,next;
}d[N*20];
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
void Init(){
	scc=cnt=tot=tp=0;
	memset(p,0,sizeof(p));
	memset(d,0,sizeof(d));
	memset(b,0,sizeof(b));
	memset(h,0,sizeof(h));
	memset(st,0,sizeof(st));
	memset(vis,0,sizeof(vis));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	memset(opp,0,sizeof(opp));
}
void edge_add(int x,int y,int op){
	if(op){Add(x,y+n*2);Add(y,x+n*2);}
	if(!op){Add(x+n*2,y);Add(y+n*2,x);}
}
void Build(int dnum){
	Init();
	for(int i=1;i<=n;i++)edge_add(key1[i],key2[i],1);
	for(int i=1;i<=dnum;i++)edge_add(door1[i],door2[i],0);
	for(int i=1;i<=n*4;i++)if(!dfn[i])Tarjan(i);
}
bool Check(){
	for(int i=1;i<=n*2;i++){
		opp[b[i]]=b[i+n*2];
		opp[b[i+n*2]]=b[i];
		if(b[i]==b[i+n*2])return false;
	}
	return true;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		key1[i]=read()+1;
		key2[i]=read()+1;
	}
	for(int i=1;i<=m;i++){
		door1[i]=read()+1;
		door2[i]=read()+1;
	}
	int l=0,r=m,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		Build(mid);
		if(Check()){
			ans=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	printf("%d",ans);
	return 0;
}