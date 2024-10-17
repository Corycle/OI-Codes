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
const int N=20005;
const int M=1<<6;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,p,cnt,Sta;
int dp[N][M],vis[N][M];
int val[N],h[N],sta[N];
struct node{int x,y;};
struct edge{int to,next,data;}d[N*20];
queue<node>q;
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],z};h[y]=cnt;
}
void Init(){
	cnt=0;Sta=1<<(n+1);
	memset(h,0,sizeof(h));
	memset(vis,0,sizeof(vis));
	memset(dp,0x3f,sizeof(dp));
	for(int i=0;i<=n;i++){
		sta[i]=1<<i;
		dp[i][sta[i]]=0;
	}
}
void SPFA(){
	while(q.size()){
		node fx=q.front();
		vis[fx.x][fx.y]=0;
		q.pop();
		for(int i=h[fx.x];i;i=d[i].next){
			int y=d[i].to;
			int S=fx.y|sta[y];
			if(dp[y][S]>dp[fx.x][fx.y]+d[i].data){
				dp[y][S]=dp[fx.x][fx.y]+d[i].data;
				if(S==fx.y&&!vis[y][S]){
					vis[y][S]=1;
					q.push((node){y,S});
				}
			}
		}
	}
}
void Steiner_Tree(){
	for(int i=0;i<Sta;i++){
		for(int j=0;j<=n+m;j++){
			if(!(i&sta[j])&&j<=n)continue;
			for(int k=i;k;k=(k-1)&i){
				dp[j][i]=min(dp[j][i],dp[j][k|sta[j]]+dp[j][(i-k)|sta[j]]);
			}
			if(dp[j][i]!=inf){
				vis[j][i]=1;
				q.push((node){j,i});
			}
		}
		SPFA();
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	while(scanf("%d%d%d",&n,&m,&p)!=EOF){
		Init();
		for(int i=1;i<=n+m;i++){
			val[i]=read();
			Add(0,i,val[i]);
		}
		for(int i=1;i<=p;i++){
			int x=read(),y=read(),z=read();
			Add(x,y,z);
		}
		Steiner_Tree();
		int ans=inf;
		for(int i=0;i<=n+m;i++){
			ans=min(ans,dp[i][Sta-1]);
		}
		printf("%d\n",ans);
	}
	return 0;
}