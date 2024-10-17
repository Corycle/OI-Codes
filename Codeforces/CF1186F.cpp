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
#define fst first
#define scd second
#define mp make_pair
#define pii pair<int,int>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
vector<pii>G[N];
int g[N],deg[N],vis[N];
struct Edge{int x,y;}E[N];
priority_queue<pii,vector<pii>,greater<pii> >q;
bool cmp(pii A,pii B){return g[A.fst]>g[B.fst];}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		E[i].x=read();E[i].y=read();deg[E[i].x]++;deg[E[i].y]++;
		G[E[i].x].push_back(mp(E[i].y,i));G[E[i].y].push_back(mp(E[i].x,i));
	}
	int num=m-(n+m+1)/2;
	if(num<=0){printf("%d\n",m);for(int i=1;i<=m;i++)printf("%d %d\n",E[i].x,E[i].y);return 0;}
	for(int i=1;i<=n;i++){g[i]=deg[i]-(deg[i]+1)/2;q.push(mp(g[i],i));}
	while(q.size()){
		int x=q.top().scd;q.pop();
		if(g[x]==0)continue;
		sort(G[x].begin(),G[x].end(),cmp);
		for(auto e:G[x]){
			int y=e.fst;
			if(vis[e.scd]||g[y]==0)continue;
			g[x]--;g[y]--;num--;vis[e.scd]=1;
			if(g[y])q.push(mp(g[y],y));
			if(!g[x]||!num)break;
		}
		if(!num)break;
	}
	printf("%d\n",(n+m+1)/2);
	for(int i=1;i<=m;i++)if(!vis[i])printf("%d %d\n",E[i].x,E[i].y);
	return 0;
}
