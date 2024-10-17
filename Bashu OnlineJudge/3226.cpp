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
const int M=1000005;
const int N=10005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
int n,m,S,T,cnt,tot,scc,top;
int st[N],id[N],pos[N],vis[N];
int h[N],b[N],deg[N],dfn[N],low[N];
double f[N],E[105],a[105][105];
struct edge{int to,next;}d[M];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void Tarjan(int x){
	dfn[x]=low[x]=++tot;
	st[++top]=x;vis[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(!dfn[y]){
			Tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(vis[y])low[x]=min(low[x],dfn[y]);
	}
	if(dfn[x]==low[x]){
		int k=0;scc++;
		do{
			k=st[top--];
			b[k]=scc;vis[k]=0;
			G[scc].push_back(k);
		}while(k!=x);
	}
}
void Gauss(){
	for(int i=1;i<=tot;i++){
		int t=i;
		double Max=abs(a[i][i]);
		for(int j=i;j<=tot;j++){
			if(Max<abs(a[j][i])){t=j;Max=abs(a[j][i]);}
		}
		swap(a[i],a[t]);
		for(int j=i+1;j<=tot;j++){
			double dlt=a[j][i]/a[i][i];
			for(int k=i;k<=tot+1;k++)a[j][k]-=a[i][k]*dlt;
		}
	}
	for(int i=tot;i>=1;i--){
		E[i]=a[i][tot+1];
		for(int j=i+1;j<=tot;j++)E[i]-=E[j]*a[i][j];
		E[i]/=a[i][i];
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();S=read();T=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		Add(x,y);deg[x]++;
	}
	Tarjan(S);
	if(!dfn[T]){puts("INF");return 0;}
	for(int i=1;i<=n;i++)vis[i]=0;
	for(int t=1;t<=scc;t++){
		tot=0;
		for(auto x:G[t]){
			vis[t]|=(x==T);
			pos[id[x]=++tot]=x;
		}
		for(auto x:G[t]){
			for(int i=h[x];i;i=d[i].next){
				vis[t]|=vis[b[d[i].to]];
			}
		}
		if(!vis[t]){puts("INF");return 0;}
		for(int i=1;i<=tot;i++){
			for(int j=1;j<=tot+1;j++)a[i][j]=0;
			a[i][i]=1;
			int x=pos[i];
			if(x==T)continue;
			a[i][tot+1]=1;
			for(int j=h[x];j;j=d[j].next){
				int y=d[j].to;
				if(b[x]==b[y]){
					a[i][id[y]]-=1.0/deg[x];
				}
				else a[i][tot+1]+=f[y]/deg[x];
			}
		}
		Gauss();
		for(int i=1;i<=tot;i++)f[pos[i]]=E[i];
	}
	printf("%.3lf",f[S]);
	return 0;
}