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
const int M=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[M][M];
int n,m,tot,cnt=1;
int id[M][M],h[N],a[N],dis[N];
struct edge{int to,next,flow;}d[N];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
}
int Sqr(int x){return x*x;}
bool BFS(int s,int t){
	for(int i=1;i<=tot;i++)dis[i]=-1;
	queue<int>q;q.push(s);dis[s]=0;
	while(q.size()){
		int x=q.front();q.pop();
		if(x==t)return true;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].flow&&dis[y]==-1){
				dis[y]=dis[x]+1;
				q.push(y);
			}
		}
	}
	return false;
}
int DFS(int x,int maxx,int t){
	if(x==t||!maxx)return maxx;
	int ans=0;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].flow&&dis[y]==dis[x]+1){
			int dlt=DFS(y,min(maxx,d[i].flow),t);
			if(!dlt)dis[y]=-1;
			d[i].flow-=dlt;
			d[i^1].flow+=dlt;
			ans+=dlt;maxx-=dlt;
			if(!maxx)return ans;
		}
	}
	return ans;
}
int Dinic(int s,int t){
	int ans=0;
	while(BFS(s,t))ans+=DFS(s,inf,t);
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	int S=++tot,T=++tot;
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]+1);
		for(int j=0;j<=n;j++){
			id[i][j]=++tot;
		}
	}
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++){
		if(i==1){
			Add(S,id[i][0],0);
			for(int j=1;j<=n;j++){
				Add(id[i][j-1],id[i][j],inf);
			}
		}
		else{
			Add(S,id[i][0],Sqr(a[i]-0));
			for(int j=1;j<=n;j++){
				Add(id[i][j-1],id[i][j],Sqr(a[i]-j));
			}
		}
		for(int j=1;j<=n;j++){
			if(s[i][j]=='N')continue;
			for(int k=1;k<=n;k++){
				Add(id[i][k],id[j][k-1],inf);
			}
		}
		Add(id[i][n],T,inf);
	}
	printf("%d",Dinic(S,T));
	return 0;
}