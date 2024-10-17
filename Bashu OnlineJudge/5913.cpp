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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
int n,m,cnt,top,scc,tot;
int h[N],b[N],rd[N],st[N],dfn[N],low[N],num[N],vis[N];
struct edge{int to,next;}d[N*10];
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
			num[scc]++;
			b[k]=scc;
			vis[k]=0;
		}while(k!=x);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();Add(x,y);
	}
	for(int i=1;i<=n;i++)if(!dfn[i])Tarjan(i);
	for(int x=1;x<=n;x++){
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(b[x]!=b[y]){
				rd[b[y]]++;
				G[b[x]].push_back(b[y]);
			}
		}
	}
	int Ans=0;
	for(int i=1;i<=scc;i++)if(!rd[i])Ans++;
	for(int x=1;x<=scc;x++){
		if(!rd[x]&&num[x]==1){
			int flag=1;
			for(auto y:G[x]){
				if(rd[y]==1){flag=0;break;}
			}
			if(flag){Ans--;break;}
		}
	}
	printf("%.6lf",(double)(n-Ans)/n);
	return 0;
}