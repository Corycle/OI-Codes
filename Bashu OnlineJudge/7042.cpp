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
const int M=100005;
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,tot,num1,num2,Max,Root;
int h[N],dis[N],pre[N],vis[N],Ans1[M],Ans2[M];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void DFS(int x,int fa,int dist){
	pre[x]=fa;dis[x]=dist;if(dist>Max){Max=dist;Root=x;}
	for(int i=h[x];i;i=d[i].next){int y=d[i].to;if(y!=fa)DFS(y,x,dist+1);}
}
void Solve(int x,int fa){
	Ans2[++num2]=x;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;
		Solve(y,x);
		Ans1[++num1]=x;
		Ans2[++num2]=++tot;
	}
}
int main(){
//	freopen("combo.in","r",stdin);
//	freopen("combo.out","w",stdout);
	n=read();tot=n;
	for(int i=1;i<n;i++){int x=read(),y=read();Add(x,y);Add(y,x);}
	Max=Root=0;DFS(1,0,0);int S=Root;
	Max=Root=0;DFS(S,0,0);int T=Root;
	for(int x=T;x;x=pre[x])vis[x]=1;
	for(int x=T;x;x=pre[x]){
		Ans2[++num2]=x;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(vis[y])continue;
			Solve(y,x);
			Ans1[++num1]=x;
			Ans2[++num2]=++tot;
		}
	}
	printf("%d\n",num1);
	for(int i=1;i<=num1;i++)printf("%d ",Ans1[i]);puts("");
	for(int i=1;i<=num2;i++)printf("%d ",Ans2[i]);puts("");
	return 0;
}