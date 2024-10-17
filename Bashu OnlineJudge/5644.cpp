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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
vector<int>G[N];
int n,m,tot,num,top,Sum,cnt=1;
struct edge{int to,next;}d[N*2];
int h[N],a[N],fa[N],st[N],dfn[N],low[N],sum[N];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void Addedge(int x,int y){G[x].push_back(y);G[y].push_back(x);}
void Tarjan(int x,int pre){
	dfn[x]=low[x]=++tot;st[++top]=x;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(i==(pre^1))continue;
		if(!dfn[y]){
			Tarjan(y,i);
			low[x]=min(low[x],low[y]);
			if(low[y]>=dfn[x]){
				int k=0;fa[++num]=x;a[num]++;Addedge(x,num);
				do{k=st[top--];fa[k]=num;a[num]++;Addedge(k,num);}while(k!=y);
			}
		}
		else low[x]=min(low[x],dfn[y]);
	}
}
void DFS1(int x){
	sum[x]=(x<=n);
	for(auto y:G[x])if(y!=fa[x]){DFS1(y);sum[x]+=sum[y];}
}
void DFS2(int x){
	for(auto y:G[x])if(y!=fa[x]){DFS2(y);Ans+=1ll*a[x]*sum[y]*(Sum-sum[y]);}
	Ans+=1ll*a[x]*sum[x]*(Sum-sum[x]);if(x<=n)Ans+=a[x]*(Sum-1);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();num=n;
	for(int i=1;i<=m;i++){int x=read(),y=read();Add(x,y);Add(y,x);}
	for(int i=1;i<=n;i++)a[i]=-1;
	for(int i=1;i<=n;i++)if(!dfn[i]){Tarjan(i,0);DFS1(i);Sum=sum[i];DFS2(i);}
	printf("%lld",Ans);
	return 0;
}