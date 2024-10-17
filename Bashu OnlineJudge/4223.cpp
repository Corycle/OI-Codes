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
const int N=10005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,p;
int tot,cnt,Flow,Cost;
int A[N],B[N],ti[N],ci[N];
int h[N],vis[N],dis[N],pre[N];
struct edge{int to,next,flow,cost;}d[N*10];
void Add(int x,int y,int f,int c){
	d[++cnt]=(edge){y,h[x],f,c};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0,-c};h[y]=cnt;
}
bool SPFA(int s,int t){
	memset(vis,0,sizeof(vis));
	memset(pre,0,sizeof(pre));
	memset(dis,0x3f,sizeof(dis));
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
	return dis[t]<inf;
}
void Adjust(int s,int t){
	int p=0,dlt=inf;
	for(int i=t;i!=s;i=d[p^1].to){
		p=pre[i];
		dlt=min(dlt,d[p].flow);
	}
	for(int i=t;i!=s;i=d[p^1].to){
		p=pre[i];
		d[p].flow-=dlt;
		d[p^1].flow+=dlt;
	}
	Flow+=dlt;
	Cost+=dlt*dis[t];
}
void Edmonds_Karp(int s,int t){
	Flow=Cost=0;
	while(SPFA(s,t))Adjust(s,t);
}
void Prepare(){
	cnt=1;tot=0;
	memset(h,0,sizeof(h));
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int CaseNum=read();
	for(int Case=1;Case<=CaseNum;Case++){
		n=read();m=read();p=read();Prepare();
		int S=++tot,T=++tot,R=++tot,sum=0;
		for(int i=1;i<=n;i++)A[i]=++tot;
		for(int i=1;i<=n;i++)B[i]=++tot;
		for(int i=1;i<=n;i++){
			int x=read();
			Add(S,A[i],x,0);
			Add(B[i],T,x,0);
			Add(R,B[i],inf,0);
			if(i!=n)Add(A[i],A[i+1],inf,0);
			sum+=x;
		}
		for(int i=1;i<=m;i++){
			int num=read(),cost=read();
			Add(S,R,num,cost);
		}
		for(int i=1;i<=p;i++){ti[i]=read();ci[i]=read();}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=p;j++){
				if(i+ti[j]+1<=n)Add(A[i],B[i+ti[j]+1],inf,ci[j]);
			}
		}
		Edmonds_Karp(S,T);
		printf("Case %d: ",Case);
		if(Flow==sum)printf("%d\n",Cost);
		else printf("impossible\n");
	}
	return 0;
}