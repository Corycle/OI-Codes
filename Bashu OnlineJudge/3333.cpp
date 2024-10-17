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
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
int n,m,cnt,top,scc,tot;
int h[N],b[N],st[N],vis[N],dfn[N],low[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void Tarjan(int x,int pre){
	int num=0;
	dfn[x]=low[x]=++tot;st[++top]=x;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(i==(pre^1))continue;
		if(!dfn[y]){
			Tarjan(y,i);
			low[x]=min(low[x],low[y]);
			if(dfn[x]<=low[y]){
				vis[x]=1;scc++;num++;
				int k=0;
				do{
					k=st[top--];
					G[scc].push_back(k);
					b[k]=scc;
				}while(k!=y);
				G[scc].push_back(x);b[x]=scc;
			}
		}
		else low[x]=min(low[x],dfn[y]);
	}
	if(!pre)vis[x]=(num>1);
}
void Prepare(){
	cnt=1;scc=tot=0;
	memset(h,0,sizeof(h));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	memset(vis,0,sizeof(vis));
}
ll Sum(int x){return x*(x-1)/2;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int Case=0;
	while(1){
		Prepare();
		n=read();if(!n)break;
		for(int i=1;i<=n;i++){
			int x=read(),y=read();
			Add(x,y);Add(y,x);
		}
		ll Ans1=0,Ans2=1;
		for(int i=1;i<=n;i++)if(!dfn[i])Tarjan(i,0);
		for(int i=1;i<=scc;i++){
			int num=0;
			for(auto x:G[i])num+=vis[x];
			if(num==0){
				Ans1=Ans1+2;
				Ans2=Ans2*Sum(G[i].size());
			}
			if(num==1){
				Ans1=Ans1+1;
				Ans2=Ans2*(G[i].size()-1);
			}
			G[i].clear();
		}
		printf("Case %d: %lld %lld\n",++Case,Ans1,Ans2);
	}
	return 0;
}