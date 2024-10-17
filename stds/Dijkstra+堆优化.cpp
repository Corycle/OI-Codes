/*====Corycle====*/
#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define fst first
#define scd second
#define mp make_pair
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e5+5;
const int M=5e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,s,cnt;
int h[N],vis[N],dis[N];
struct edge{int to,next,dist;}d[M];
void Add(int x,int y,int z){d[++cnt]=(edge){y,h[x],z};h[x]=cnt;}
void Dijsktra(){
	priority_queue<pii,vector<pii>,greater<pii> >q;
	for(int i=1;i<=n;i++)dis[i]=(1ll<<31)-1;
	dis[s]=0;q.push(mp(0,s));
	while(!q.empty()){
		int x=q.top().scd;q.pop();
		if(vis[x])continue;vis[x]=1;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(dis[y]>dis[x]+d[i].dist){
				dis[y]=dis[x]+d[i].dist;
				q.push(mp(dis[y],y));
			}
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();s=read();
	for(int i=1;i<=m;i++){int x=read(),y=read();Add(x,y,read());}
	Dijsktra();
	for(int i=1;i<=n;i++)printf("%d ",dis[i]);
	return 0;
}
