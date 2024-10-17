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
const int P=2005;
const int M=50;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char a[M][M];
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
int n,m,tot,Sum,cnt=1;
int h[N],dis[N],Dis[M][M],id[M][M][P];
struct edge{int to,next,flow;}d[N*40];
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
void Prepare(){
	queue<int>qx,qy;
	memset(Dis,-1,sizeof(Dis));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]=='D'){
				Dis[i][j]=0;
				qx.push(i);qy.push(j);
			}
		}
	}
	while(qx.size()){
		int x=qx.front();qx.pop();
		int y=qy.front();qy.pop();
		for(int i=0;i<4;i++){
			int fx=x+dx[i],fy=y+dy[i];
			if(fx<1||fx>n||fy<1||fy>m)continue;
			if(Dis[fx][fy]==-1&&a[fx][fy]=='.'){
				Dis[fx][fy]=Dis[x][y]+1;
				qx.push(fx);qy.push(fy);
			}
		}
	}
}
int Solve(){
	int ans=0,sum=0,S=++tot,T=++tot;
	while(1){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(a[i][j]=='#')continue;
				id[i][j][ans]=++tot;
				if(a[i][j]=='D')Add(id[i][j][ans],T,1);
				if(!ans&&a[i][j]=='.')Add(S,id[i][j][ans],1);
				if(ans){
					Add(id[i][j][ans-1],id[i][j][ans],inf);
					for(int k=0;k<4;k++){
						int x=i+dx[k],y=j+dy[k];
						if(x<1||x>n||y<1||y>m||a[x][y]=='X')continue;
						Add(id[x][y][ans-1],id[i][j][ans],inf);
					}
				}
			}
		}
		sum+=Dinic(S,T);
		if(sum>=Sum)break;
		ans++;
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		scanf("%s",a[i]+1);
	}
	Prepare();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]=='.'){
				Sum++;
				if(Dis[i][j]==-1){
					printf("impossible");
					return 0;
				}
			}
		}
	}
	printf("%d",Solve());
	return 0;
}