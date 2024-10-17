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
const int N=405;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char op[10];
ll Flow,Cost,sum;
int n,m,cnt=1,a[N],b[N];
int h[N],dis[N],vis[N],pre[N];
struct edge{int to,next,flow,cost;}d[N*N];
void Add(int x,int y,int f,int c){
	d[++cnt]=(edge){y,h[x],f,c};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0,-c};h[y]=cnt;
}
bool SPFA(int s,int t){
	for(int i=1;i<=t;i++){dis[i]=inf;vis[i]=pre[i]=0;}
	queue<int>q;q.push(s);dis[s]=0;
	while(q.size()){
		int x=q.front();q.pop();vis[x]=0;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].flow&&dis[y]>dis[x]+d[i].cost){
				dis[y]=dis[x]+d[i].cost;pre[y]=i;
				if(!vis[y]){vis[y]=1;q.push(y);}
			}
		}
	}
	return dis[t]!=inf;
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
	Flow+=dlt;Cost+=1ll*dlt*dis[t];
}
void Edmonds_Karp(int s,int t){
	Flow=Cost=0;
	while(SPFA(s,t))Adjust(s,t);
}
int main(){
//	freopen("seq.in","r",stdin);
//	freopen("seq.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=a[i]-a[i-1];
	int S=n+2,T=n+3;
	Add(S,1,inf,0);Add(S,n+1,inf,0);
	for(int i=2;i<=n;i++){
		if(b[i]>0)Add(S,i,b[i],0);
		else{sum-=b[i];Add(i,T,-b[i],0);}
	}
	for(int i=1;i<=m;i++){
		scanf("%s",op);
		int l=read(),c=read();
		for(int i=1;i+l-1<=n;i++){
			if(op[0]=='+')Add(i+l,i,inf,c);
			if(op[0]=='-')Add(i,i+l,inf,c);
		}
	}
	Edmonds_Karp(S,T);
	printf("%lld",Flow==sum?Cost:-1);
	return 0;
}