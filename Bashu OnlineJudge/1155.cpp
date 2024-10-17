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
int n,m,p,cnt,Sta,tot;
int ans1,ans2,num1,num2;
int h[N],sta[N],type[N],data[N];
int dp[N][N],vis[N][N],num[N],ans[N];
struct edge{int to,next,data;}d[N*N];
struct node{int x,y;};
queue<node>q;
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],z};h[y]=cnt;
}
void Init(){
	memset(h,0,sizeof(h));
	memset(vis,0,sizeof(vis));
	memset(sta,0,sizeof(sta));
	memset(dp,0x3f,sizeof(dp));
	memset(ans,0x3f,sizeof(ans));
	cnt=num1=num2=ans1=ans2=tot=0;
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
	Sta=1<<m;
	for(int i=0;i<Sta;i++){
		for(int j=1;j<=n;j++){
			if(!(i&sta[j])&&sta[j])continue;
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
bool Check(int x){
	int Ans=0;
	for(int i=0;x;i++){
		if(x&1)Ans+=i<num1?data[i]:-1;
		x>>=1;
	}
	return Ans>=0;
}
int Count(int x){
	int Ans=0;
	for(int i=0;x;i++){
		if(x&1&&i>=num1)Ans++;
		x>>=1;
	}
	return Ans;
}
void Solve(){
	Steiner_Tree();
	for(int i=1;i<Sta;i++){
		for(int j=1;j<=n;j++){
			ans[i]=min(ans[i],dp[j][i]);
		}
	}
	for(int i=1;i<Sta;i++){
		if(Check(i)){//工厂多还是资源多 
			for(int k=i;k;k=(k-1)&i){
				int x=k,y=i-k;
				if(ans[x]!=inf&&ans[y]!=inf&&Check(x)&&Check(y)){
					ans[i]=min(ans[i],ans[x]+ans[y]);
				}
			}
			if(ans[i]==inf)continue;
			int tmp=Count(i);//资源数 即可满足的数量 
			if(tmp>ans1||(tmp==ans1&&ans[i]<ans2)){
				ans1=tmp;ans2=ans[i];
			}
		}
	}
	ans1+=tot;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	while(scanf("%d",&n)!=EOF){
		Init();
		for(int i=1;i<=n;i++){
			num[i]=read();type[i]=read();
			if(num[i]&&type[i]){
				tot++;
				num[i]--;
				type[i]--;
			}
			if(num[i]){
				sta[i]=1<<num1;
				data[num1]=num[i];
				num1++;
			}
		}
		for(int i=1;i<=n;i++){
			if(type[i]){
				sta[i]=1<<(num1+num2);
				num2++;
			}
			dp[i][sta[i]]=0;
		}
		m=num1+num2;
		p=read();
		while(p--){
			int x=read(),y=read(),z=read();
			Add(x,y,z);
		}
		Solve();
		printf("%d %d\n",ans1,ans2);
	}
	return 0;
}