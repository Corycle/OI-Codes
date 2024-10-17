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
const int N=20005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,g,Ans,tot,cnt=1;
int a[N],h[N],dis[N];
struct edge{int to,next,flow;}d[N*100];
void Add(int x,int y,int f){
	d[++cnt]=(edge){y,h[x],f};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
}
bool BFS(int s,int t){
	for(int i=1;i<=tot;i++)dis[i]=-1;
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
int DFS(int x,int maxn,int t){
	if(x==t||!maxn)return maxn;
	int ans=0;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].flow&&dis[y]==dis[x]+1){
			int dlt=DFS(y,min(d[i].flow,maxn),t);
			if(!dlt)dis[y]=-1;
			d[i].flow-=dlt;
			d[i^1].flow+=dlt;
			maxn-=dlt;ans+=dlt;
			if(!maxn)return ans;
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
	n=read();m=read();g=read();
	int S=n+1,T=n+2;tot=n+2;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++){
		int x=read();
		if(a[i]==0){Add(S,i,0);Add(i,T,x);}
		if(a[i]==1){Add(S,i,x);Add(i,T,0);}
	}
	while(m--){
		tot++;
		int op=read(),w=read(),num=read();
		for(int i=1;i<=num;i++){
			int x=read();
			if(op==0)Add(x,tot,inf);
			if(op==1)Add(tot,x,inf);
		}
		int t=read();
		if(op==0)Add(tot,T,w+g*t);
		if(op==1)Add(S,tot,w+g*t);
		Ans+=w;
	}
	printf("%d",Ans-Dinic(S,T));
	return 0;
}