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
const int Mul=1e6;
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,Ans,h[N],vis[N],dis[N];
struct edge{int to,next,flow,cost;}d[N*2];
void Add(int x,int y,int f,int c){d[++cnt]=(edge){y,h[x],f,c};h[x]=cnt;}
void Solve(int Min){
	for(int i=1;i<=n;i++){vis[i]=0;dis[i]=inf;}
	priority_queue<pii,vector<pii>,greater<pii> >q;
	dis[1]=0;q.push(mp(0,1));
	while(q.size()){
		int x=q.top().scd;q.pop();
		if(vis[x])continue;vis[x]=1;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].flow>=Min&&dis[y]>dis[x]+d[i].cost){
				dis[y]=dis[x]+d[i].cost;q.push(mp(dis[y],y));
			}
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){int x=read(),y=read(),c=read(),f=read();Add(x,y,f,c);Add(y,x,f,c);}
	for(int i=1;i<N;i++){Solve(i);Ans=max(Ans,(int)((double)Mul*i/dis[n]));}
	printf("%d\n",Ans);
	return 0;
}
