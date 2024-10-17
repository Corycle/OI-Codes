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
const int N=10005;
const int M=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot,cnt=1;
int a[M],id[M][M],c[M][M];
int h[N],A[N],B[N],H[N],dis[N];
struct edge{int to,next,flow;}d[N*20];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
}
bool BFS(int s,int t){
	for(int i=1;i<=tot;i++)dis[i]=-1;
	queue<int>q;q.push(s);dis[s]=0;
	while(q.size()){
		int x=q.front();q.pop();
		if(x==t)return true;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].flow&&dis[y]==-1){
				dis[y]=dis[x]+1;q.push(y);
			}
		}
	}
	return false;
}
int DFS(int x,int maxx,int t){
	if(x==t||!maxx)return maxx;
	int ans=0;
	for(int &i=H[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].flow&&dis[y]==dis[x]+1){
			int dlt=DFS(y,min(d[i].flow,maxx),t);
			if(!dlt)dis[y]=-1;
			d[i].flow-=dlt;
			d[i^1].flow+=dlt;
			maxx-=dlt;ans+=dlt;
			if(!maxx)return ans;
		}
	}
	return ans;
}
int Dinic(int s,int t){
	int Flow=0;
	while(BFS(s,t)){
		for(int i=1;i<=tot;i++)H[i]=h[i];
		Flow+=DFS(s,inf,t);
	}
	return Flow;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	int S=++tot,T=++tot,Max=0,Sum=0;
	for(int i=1;i<=n;i++){
		A[i]=++tot;a[i]=-read();
		if(a[i]>0){Sum+=a[i];Add(S,A[i],a[i]);}else Add(A[i],T,-a[i]);
		if(!B[a[i]]){B[a[i]]=++tot;Add(B[a[i]],T,m*a[i]*a[i]);}
		Add(A[i],B[a[i]],inf);Max=max(Max,a[i]);
	}
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			c[i][j]=read();
			id[i][j]=++tot;
			if(c[i][j]>0){
				Sum+=c[i][j];
				Add(S,id[i][j],c[i][j]);
			}
			else Add(id[i][j],T,-c[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			Add(id[i][j],id[i+1][j],inf);
			Add(id[i][j],id[i][j-1],inf);
		}
		Add(id[i][i],A[i],inf);
	}
	printf("%d",Sum-Dinic(S,T));
	return 0;
}