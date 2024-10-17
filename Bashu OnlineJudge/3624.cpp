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
const int N=3e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
int n,m,tot,top,scc,cnt=1;
int a[N],b[N],h[N],st[N],sum[N],son[N],num[N],dfn[N],low[N],Ans[N];
struct edge{int to,next;}d[N];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void Tarjan(int x,int pre){
	dfn[x]=low[x]=++tot;st[++top]=x;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(i==(pre^1))continue;
		if(!dfn[y]){
			Tarjan(y,i);
			low[x]=min(low[x],low[y]);
			if(low[y]>=dfn[x]){
				int k=0;scc++;G[x].push_back(scc);
				do{k=st[top--];G[scc].push_back(k);}while(k!=y);
			}
		}
		else low[x]=min(low[x],dfn[y]);
	}
}
struct Ques{int op,y,id;};
vector<Ques>F[N];
struct BIT{
	int c[N];
	int lowbit(int x){return x&(-x);}
	void Add(int x,int y){for(;x<N;x+=lowbit(x))c[x]+=y;}
	int Ask(int x){int ans=0;for(;x>=1;x-=lowbit(x))ans+=c[x];return ans;}
}tree[2];
void update(int x,int addv){
	if(x>n)return;
	if(num[a[x]])tree[num[a[x]]&1].Add(a[x],-1);
	num[a[x]]+=addv;
	if(num[a[x]])tree[num[a[x]]&1].Add(a[x],1);
}
void Update(int x,int addv){
	update(x,addv);
	for(auto y:G[x])Update(y,addv);
}
void DFS1(int x){
	sum[x]=1;
	for(auto y:G[x]){
		DFS1(y);sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
	}
}
void DFS2(int x,int flag){
	for(auto y:G[x])if(y!=son[x])DFS2(y,0);
	if(son[x])DFS2(son[x],1);update(x,1);
	for(auto y:G[x])if(y!=son[x])Update(y,1);
	for(auto Q:F[x])Ans[Q.id]=tree[Q.op].Ask(Q.y);
	if(!flag)Update(x,-1);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();scc=n;
	for(int i=1;i<=n;i++)a[i]=b[i]=read();
	sort(b+1,b+n+1);b[0]=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+b[0]+1,a[i])-b;
	for(int i=1;i<=m;i++){int x=read(),y=read();Add(x,y);Add(y,x);}
	int Q=read();
	for(int i=1;i<=Q;i++){
		int op=read(),x=read(),y=upper_bound(b+1,b+b[0]+1,read())-b-1;
		F[x].push_back((Ques){op,y,i});
	}
	Tarjan(1,0);DFS1(1);DFS2(1,0);
	for(int i=1;i<=Q;i++)printf("%d\n",Ans[i]);
	return 0;
}