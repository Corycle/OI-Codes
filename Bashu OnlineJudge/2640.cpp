#include<iostream>
#include<cstdio>
#include<cstring>
#define Min(a,b) ((a)<(b)?(a):(b))
#define Max(a,b) ((a)>(b)?(a):(b))
using namespace std;
const int MAXN = 100010, MAXM = 1000010;
int N, M, ans;
 
struct Node {
	int to; Node*next;
}Edge[MAXM], *ecnt=Edge, *adj[MAXM];
inline void addedge(int a,int b) {
	++ecnt; ecnt->to = b;
	ecnt->next=adj[a]; adj[a] = ecnt;
}
 
int belong[MAXN], bcnt;//每个原图中的点属于哪个连通块
int bmx[MAXN], bmn[MAXN];//缩点以后每个连同块中的最大和最小值
int tmr, dfn[MAXN], low[MAXN];
int sta[MAXN], tp;
int val[MAXN];
int x[MAXM], y[MAXM], type[MAXM];
bool insta[MAXN];
 
void tarjan(int u)
{
	dfn[u] = low[u] = ++tmr;
	sta[++tp] = u;
	insta[u] = 1;
	for (Node*p = adj[u]; p; p = p->next) {
		int &v = p->to;
		if (!dfn[v]) {
			tarjan(v);
			low[u] = Min(low[u], low[v]);
		}
		else if (insta[v])
			low[u] = Min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		++bcnt;
		int i;
		do {
			i = sta[tp];
			belong[i] = bcnt;
			bmx[bcnt] = Max(bmx[bcnt], val[i]);
			bmn[bcnt] = Min(bmn[bcnt], val[i]);
			insta[i] = 0; --tp;
		} while (tp>0 && i!=u);
	}
}
 
int f[MAXN];
bool vis[MAXN];
void dfs(int u) {
	vis[u] = 1;
	if (u==belong[N]) f[u] = Max(f[u], bmx[u]);
	for (Node*p = adj[u]; p; p = p->next) {
		if (!vis[p->to]) dfs(p->to);
		f[u] = Max(f[u], f[p->to]);
	}
	if (f[u]) f[u] = Max(f[u], bmx[u]);//如果f[u]为0，说明它根本无法到达终点，也就是废点
	ans = Max(ans, f[u] - bmn[u]);//以后可卖出的最高价-当前块中的最低进价
}
 
int main()
{
	int i;
	scanf("%d%d", &N, &M);
	for (i = 1; i<=N; ++i) {
		scanf("%d", val+i);
		bmx[i]=-1, bmn[i]=999999;
	}
	for (i = 1; i<=M; ++i) {
		scanf("%d%d%d", &x[i], &y[i], &type[i]);
		addedge(x[i], y[i]);
		if (type[i]==2) addedge(y[i], x[i]);
	}
	tarjan(1);
	memset(adj, 0, sizeof adj);
	ecnt = Edge;
	for (i = 1; i<=M; ++i)
		if (belong[x[i]] != belong[y[i]])
			addedge(belong[x[i]], belong[y[i]]);
	dfs(belong[1]);
	printf("%d\n", ans);
	return 0;
}
