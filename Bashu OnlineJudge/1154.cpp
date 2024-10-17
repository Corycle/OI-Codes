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
const int N=2005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,p,cnt,Sta;
int dp[N][N],vis[N][N],num[N];
int val[N],h[N],sta[N],ans[N];
struct node{int x,y;};
struct edge{int to,next,data;}d[N*20];
queue<node>q;
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],z};h[y]=cnt;
}
int Get(){
	int x=read();
	if(x<=n)return x;
	if(x>m-n)return x-m+2*n;
	return x+n;
}
void Init(){
	cnt=0;
	memset(h,0,sizeof(h));
	memset(vis,0,sizeof(vis));
	memset(dp,0x3f,sizeof(dp));
	for(int i=1;i<=n*2;i++){
		sta[i]=1<<(i-1);
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
	Sta=1<<(n+n);
	for(int i=0;i<Sta;i++){
		for(int j=0;j<=m;j++){
			if(!(i&sta[j])&&j<=n*2)continue;
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
int Check(int x){
	int sum=0;
	for(int i=1;i<=n;i++){
		if(x&sta[i]&&x&sta[i+n])sum++;
	}
	return sum;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int Case=read();
	while(Case--){
		m=read();p=read();n=read();
		Init();
		for(int i=1;i<=p;i++){
			int x=Get(),y=Get(),z=read();
			Add(x,y,z);
		}
		Steiner_Tree();
		for(int i=0;i<Sta;i++){
			ans[i]=inf;
			num[i]=Check(i);
			if(num[i]){
				for(int j=1;j<=m;j++){
					ans[i]=min(ans[i],dp[j][i]);
				}
			}
		}
		for(int i=0;i<Sta;i++){
			if(num[i]){
				for(int j=i;j;j=(j-1)&i){
					if(num[i])ans[i]=min(ans[i],ans[j]+ans[i-j]);
				}
			}
		}
		if(ans[Sta-1]==inf)printf("No solution\n");
		else printf("%d\n",ans[Sta-1]);
	}
	return 0;
}