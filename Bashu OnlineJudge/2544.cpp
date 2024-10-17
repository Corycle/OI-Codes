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
const int N=10005;
const int M=5005;
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
}d[M*4];
struct Line{
	int s,t;
}l[M];
bool Cross(Line x,Line y){
	return (x.s<y.s&&y.s<x.t&&x.t<y.t)||(x.s>y.s&&y.s>x.t&&x.t>y.t);
}
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
	m=read();n=read();
	//n:line  m:point
	for(int i=1;i<=n;i++){
		l[i].s=read();
		l[i].t=read();
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(Cross(l[i],l[j])){
				edge_add(i*2-1,j*2);
				edge_add(i*2,j*2-1);
				edge_add(j*2-1,i*2);
				edge_add(j*2,i*2-1);
			}
		}
	}
	for(int i=1;i<=n*2;i++){
		if(!dfn[i])Tarjan(i);
	}
	for(int i=1;i<=n;i++){
		if(b[i*2]==b[i*2-1]){
			printf("the evil panda is lying again");
			return 0;
		}
	}
	printf("panda is telling the truth...");
	return 0;
}