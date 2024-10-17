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
const int M=50;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,p,tot,cnt=1;
int h[N],P[N],fa[N],dis[N],num[N],a[M][N];
struct edge{int to,next,flow;}d[N*10];
int Find(int x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
void Union(int x,int y){fa[Find(x)]=Find(y);}
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
}
bool BFS(int s,int t){
	memset(dis,-1,sizeof(dis));
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
	int ans=0;
	if(x==t||!maxx)return maxx;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].flow&&dis[y]==dis[x]+1){
			int dlt=DFS(y,min(d[i].flow,maxx),t);
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
	n=read()+2;m=read();p=read();
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		P[i]=read();num[i]=read();
		for(int j=0;j<num[i];j++){
			a[i][j]=read()+2;
			if(j)Union(a[i][j-1],a[i][j]);
		}
	}
	if(Find(1)!=Find(2)){printf("0");return 0;}
	int sum=0,ans=0,S=0,T=1e5;
	while(1){
		Add(ans*n+1,T,inf);//Moon -> T
		Add(S,ans*n+2,inf);//S -> Earth
		if(ans){
			for(int i=1;i<=n;i++)Add((ans-1)*n+i,ans*n+i,inf);
			for(int i=1;i<=m;i++){
				int x=a[i][(ans-1)%num[i]];
				int y=a[i][ans%num[i]];
				Add((ans-1)*n+x,ans*n+y,P[i]);
			}
		}
		sum+=Dinic(S,T);
		if(sum>=p)break;
		ans++;
	}
	printf("%d",ans);
	return 0;
}