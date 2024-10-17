#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=40005;
const int M=205;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[M];
int n,cnt=1,tot,sum;
int a[M][M],id[M][M],h[N],dis[N];
int dx[8]={1,-1,2,-2,1,-1,2,-2};
int dy[8]={2,2,1,1,-2,-2,-1,-1};
struct edge{
	int to,next,flow;
}d[N*20];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
}
bool BFS(int s,int t){
	queue<int>q;
	memset(dis,-1,sizeof(dis));
	q.push(s);dis[s]=0;
	while(q.size()){
		int x=q.front();q.pop();
		if(x==t)return true;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(dis[y]==-1&&d[i].flow){
				dis[y]=dis[x]+1;
				q.push(y);
			}
		}
	}
	return false;
}
int DFS(int x,int maxx,int t){
	int ans=0,dlt=0;
	if(x==t||!maxx)return maxx;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].flow&&dis[y]==dis[x]+1){
			dlt=DFS(y,min(maxx,d[i].flow),t);
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
//	freopen("attack.in","r",stdin);
//	freopen("attack.out","w",stdout);
	n=read();
	int S=0,T=n*n+1;
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=n;j++){
			a[i][j]=s[j]-'0';
			id[i][j]=++tot;
		}
	}
	for(int x=1;x<=n;x++){
		for(int y=1;y<=n;y++){
			if(a[x][y])continue;
			sum++;
			if((x+y)%2==1)Add(id[x][y],T,1);
			if((x+y)%2==0){
				Add(S,id[x][y],1);
				for(int k=0;k<8;k++){
					int fx=x+dx[k],fy=y+dy[k];
					if(fx<1||fy<1||fx>n||fy>n)continue;
					if(a[fx][fy])continue;
					Add(id[x][y],id[fx][fy],1);
				}
			}
		}
	}
	int ans=sum-Dinic(S,T);
	printf("%d\n",ans);
	return 0;
}
