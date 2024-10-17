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
const int N=2005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans,dis[N];
int n,K,t1,t2,cnt=1;
int h[N],s[N],e[N],vis[N],pre[N],pos[N];
struct edge{int to,next,flow,cost;}d[N*100];
void Add(int x,int y,int f,int c){
	d[++cnt]=(edge){y,h[x],f,c};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0,-c};h[y]=cnt;
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
	return (dis[t]!=-inf);
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
	Ans+=dlt*dis[t];
}
void Edmonds_Karp(int s,int t){
	while(SPFA(s,t))Adjust(s,t);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();K=read();t1=read();t2=read();
	for(int i=1;i<=n;i++)s[i]=read();
	for(int i=1;i<=n;i++)e[i]=read();
	int S=n+1,P=n+2,T=n+3;
	for(int i=1;i<=n;i++){
		Ans+=s[i];
		Add(i,(i+1<=n?i+1:T),K-t1-t2,0);
		Add(i,(i+K<=n?i+K:T),1,e[i]-s[i]);
		pos[i]=cnt;
	}
	for(int i=1;i<=K;i++)Add(P,i,inf,0);
	Add(S,P,K-t1,0);
	Edmonds_Karp(S,T);
	printf("%lld\n",Ans);
	for(int i=1;i<=n;i++){
		printf("%c",(d[pos[i]].flow?'E':'S'));
	}
	return 0;
}