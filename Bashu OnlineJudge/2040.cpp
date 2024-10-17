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
const int M=4000005;
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
int n,m,tot,cnt=1;
int a[N],h[N],pre[N],dis[N],vis[N],prime[N];
struct edge{int to,next,flow,cost;}d[M];
void Add(int x,int y,int f,int c){
	d[++cnt]=(edge){y,h[x],f,c};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0,-c};h[y]=cnt;
}
void Prepare(int maxn){
	m=(int)(sqrt(maxn));
	for(int i=2;i<=maxn;i++){
		if(!vis[i])prime[++tot]=i;
		for(int j=1;j<=tot&&1ll*i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
}
bool SPFA(int s,int t){
	for(int i=1;i<=t;i++){dis[i]=-inf;vis[i]=pre[i]=0;}
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
	return (dis[t]>0);
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
	Ans+=1ll*dlt*dis[t];
}
void Edmonds_Karp(int s,int t){
	while(SPFA(s,t))Adjust(s,t);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Prepare(n);
	int S=tot+1,T=tot+2,t=0;
	for(int i=1;i<=tot;i++){
		a[i]=prime[i];
		while(1ll*a[i]*prime[i]<=n)a[i]*=prime[i];
		Ans+=a[i];
		if(prime[i]<=m){Add(S,i,1,0);t=i;}
		else{
			Add(i,T,1,0);
			for(int j=1;j<=t&&1ll*prime[i]*prime[j]<=n;j++){
				int p=prime[i]*prime[j];
				while(1ll*p*prime[j]<=n)p*=prime[j];
				if(p-a[i]-a[j]>0)Add(j,i,1,p-a[i]-a[j]);
			}
		}
	}
	Edmonds_Karp(S,T);
	Ans++;
	printf("%lld",Ans);
	return 0;
}