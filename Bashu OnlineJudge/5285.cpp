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
const int N=2e5+5;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot,cnt;
vector<int>G1[N],G2[N],A[N],B[N];
int b[N],f[N],h[N],rd[N],fa[N],p[N][M];
int prt[N],dfn[N],pos[N],dep[N],Min[N],sum[N];
struct edge{int to,next;}d[N];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
int Find(int x){
	if(x==fa[x])return x;
	int tmp=fa[x];fa[x]=Find(fa[x]);
	if(dfn[f[Min[tmp]]]<dfn[f[Min[x]]])Min[x]=Min[tmp];
	return fa[x];
}
void DFS(int x){
	pos[dfn[x]=++tot]=x;
	if(prt[x]){
		A[prt[x]].push_back(x);
		B[x].push_back(prt[x]);
	}
	for(auto y:G1[x])if(!dfn[y]){prt[y]=x;DFS(y);}
}
int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--){
		if(dep[x]-(1<<k)>=dep[y])x=p[x][k];
	}
	if(x==y)return x;
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--){
		if(p[x][k]!=p[y][k]){x=p[x][k];y=p[y][k];}
	}
	return p[x][0];
}
void Solve(){
	for(int i=tot;i>=2;i--){
		int x=pos[i],tmp=n;
		for(auto y:G2[x]){
			if(!dfn[y])continue;
			if(dfn[y]<dfn[x])tmp=min(tmp,dfn[y]);
			else{Find(y);tmp=min(tmp,dfn[f[Min[y]]]);}
		}
		f[x]=pos[tmp];fa[x]=prt[x];
		A[f[x]].push_back(x);
		B[x].push_back(f[x]);
	}
	queue<int>q;
	for(int x=1;x<=n;x++)for(auto y:A[x])rd[y]++;
	for(int i=1;i<=n;i++)if(!rd[i])q.push(i);
	while(q.size()){
		int x=q.front();q.pop();b[++b[0]]=x;
		for(auto y:A[x])if(!(--rd[y]))q.push(y);
	}
	for(int i=1;i<=b[0];i++){
		int x=b[i],num=B[x].size();
		if(num){
			p[x][0]=B[x][0];
			for(int j=1;j<num;j++)p[x][0]=LCA(p[x][0],B[x][j]);
		}
		dep[x]=dep[p[x][0]]+1;Add(p[x][0],x);
		for(int j=1;j<M;j++)p[x][j]=p[p[x][j-1]][j-1];
	}
}
void Calc(int x){
	sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		Calc(y);sum[x]+=sum[y];
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		G1[x].push_back(y);
		G2[y].push_back(x);
	}
	for(int i=1;i<=n;i++)f[i]=fa[i]=Min[i]=i;
	DFS(1);Solve();Calc(1);
	for(int i=1;i<=n;i++)printf("%d ",sum[i]);
	return 0;
}