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
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
int n,m,tot,Max,MaxL;
int b[N],L[N],P[N],fa[N],dis[N],pre[N],Ans[N];
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
void Union(int x,int y){fa[Find(x)]=Find(y);}
bool cmp(int x,int y){return L[x]>L[y];}
void DFS(int x,int fa,int dist){
	dis[x]=dist;pre[x]=fa;
	if(dis[x]>dis[Max])Max=x;
	for(auto y:G[x])if(y!=fa)DFS(y,x,dist+1);
}
void Solve(int x){
	tot++;Max=0;DFS(x,0,0);x=Max;Max=0;DFS(x,0,0);int y=Max;
	L[tot]=dis[y];while(dis[y]>L[tot]/2)y=pre[y];P[tot]=y;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		int x=read(),y=read();Union(x,y);
		G[x].push_back(y);G[y].push_back(x);
	}
	dis[0]=-1;
	for(int i=1;i<=n;i++)if(i==Find(i))Solve(i);
	for(int i=1;i<=tot;i++)MaxL=max(MaxL,L[i]);
//	for(int i=1;i<=tot;i++)cout<<L[i]<<" "<<P[i]<<endl;
	int Pos=0;Ans[0]=inf;
	for(int i=1;i<=tot;i++){
		for(int j=1;j<=tot;j++)b[j]=j;
		swap(b[1],b[i]);sort(b+2,b+tot+1,cmp);Ans[i]=MaxL;
		if(tot>=2)Ans[i]=max(Ans[i],(L[i]+1)/2+(L[b[2]]+1)/2+1);
		if(tot>=3)Ans[i]=max(Ans[i],(L[b[2]]+1)/2+(L[b[3]]+1)/2+2);
		if(Ans[i]<Ans[Pos])Pos=i;
	}
	printf("%d\n",Ans[Pos]);
	for(int i=1;i<Pos;i++)printf("%d %d\n",P[i],P[Pos]);
	for(int i=tot;i>Pos;i--)printf("%d %d\n",P[i],P[Pos]);
	return 0;
}
