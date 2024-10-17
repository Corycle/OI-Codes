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
const ll INF=1e18;
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot,cnt=1;
ll Flow,Cost,dis[N];
int h[N],A[N],B[N],a[N],b[N],c[N],vis[N],pre[N];
struct edge{int to,next,flow;ll cost;}d[N*N];
void Add(int x,int y,int f,ll c){
	d[++cnt]=(edge){y,h[x],f,c};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0,-c};h[y]=cnt;
}
int Rand(int x){return (1ll*rand()*rand()+rand())%x+1;}
int Pow(int x,int y,int mod){
	int ans=1;
	while(y){if(y&1)ans=1ll*ans*x%mod;x=1ll*x*x%mod;y>>=1;}
	return ans;
}
bool Miller_Rabin(int n){
	if(n==2)return true;
	if(n<2||!(n&1))return false;
	int m=n-1,k=0;while(!(m&1)){m>>=1;k++;}
	for(int i=1;i<=10;i++){
		int a=Rand(n-1),x=0,y=Pow(a,m,n);
		for(int j=1;j<=k;j++){
			x=y;y=1ll*x*x%n;
			if(y==1&&x!=1&&x!=n-1)return false;
		}
		if(y!=1)return false;
	}
	return true;
}
bool SPFA(int s,int t){
	for(int i=1;i<=tot;i++){dis[i]=-INF;vis[i]=pre[i]=0;}
	queue<int>q;q.push(s);dis[s]=0;
	while(q.size()){
		int x=q.front();q.pop();vis[x]=0;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].flow&&dis[y]<dis[x]+d[i].cost){
				dis[y]=dis[x]+d[i].cost;pre[y]=i;
				if(!vis[y]){vis[y]=1;q.push(y);}
			}
		}
	}
	return (Cost+dis[t]>=0);
}
void Adjust(int s,int t){
	int dlt=inf;
	for(int i=t;i!=s;i=d[pre[i]^1].to){
		dlt=min(dlt,d[pre[i]].flow);
	}
	for(int i=t;i!=s;i=d[pre[i]^1].to){
		d[pre[i]].flow-=dlt;
		d[pre[i]^1].flow+=dlt;
	}
	if(Cost+dlt*dis[t]>=0){
		Flow+=dlt;
		Cost+=dlt*dis[t];
	}
	else{
		int flow=min((ll)dlt,Cost/(-dis[t]));
		Flow+=flow;
		Cost+=flow*dis[t];
	}
}
void Edmonds_Karp(int s,int t){
	while(SPFA(s,t))Adjust(s,t);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	srand(time(NULL));
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=n;i++)c[i]=read();
	int S=++tot,T=++tot;
	for(int i=1;i<=n;i++){
		A[i]=++tot;B[i]=++tot;
		Add(S,A[i],b[i],0);
		Add(B[i],T,b[i],0);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(a[j]%a[i]==0&&Miller_Rabin(a[j]/a[i])){
				Add(A[i],B[j],inf,1ll*c[i]*c[j]);
				Add(A[j],B[i],inf,1ll*c[i]*c[j]);
			}
		}
	}
	Edmonds_Karp(S,T);
	printf("%lld",Flow/2);
	return 0;
}