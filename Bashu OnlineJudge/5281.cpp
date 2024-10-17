/*====Corycle====*/
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
#define pii pair<int,int>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=4000005;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
int n,m,cnt,tot,Flow,Cost;
int a[N],A[N],B[N],h[N],f[N],dis[N],pre[N];
struct edge{int to,next,flow,cost;}d[N];
void Add(int x,int y,int f,int c){
	d[++cnt]=(edge){y,h[x],f,c};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0,-c};h[y]=cnt;
}
bool Dijkstra(int s,int t){
	priority_queue<pii,vector<pii>,greater<pii> >q;
	for(int i=1;i<=tot;i++){dis[i]=inf;pre[i]=0;}
	dis[s]=0;q.push(make_pair(0,s));
	while(q.size()){
		int x=q.top().second;
		int dist=q.top().first;q.pop();
		if(dis[x]<dist)continue;//第一遍可能会重复更新，即堆优化spfa
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].flow&&dis[y]>dis[x]+d[i].cost+f[x]-f[y]){
				dis[y]=dis[x]+d[i].cost+f[x]-f[y];pre[y]=i;
				q.push(make_pair(dis[y],y));
			}
		}
	}
	return dis[t]!=inf;
}
void Adjust(int s,int t){
	int p=0,dlt=inf;
	for(int i=1;i<=tot;i++)f[i]+=dis[i];
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
	Cost+=dlt*f[t];
}
int MCMF(int s,int t){
	Cost=Flow=0;
	for(int i=1;i<=tot;i++)f[i]=0;
	while(Dijkstra(s,t))Adjust(s,t);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		cnt=1;tot=0;
		n=read();m=read();
		int s=++tot,t=++tot;
		int S=++tot,T=++tot;
		for(int i=1;i<=n;i++)A[i]=++tot;
		for(int i=1;i<=n;i++)B[i]=++tot;
		for(int i=1;i<=tot;i++)h[i]=0;
		for(int i=1;i<=n;i++){
			a[i]=read();
			Add(s,A[i],1,0);
			Add(B[i],t,1,0);
			Add(A[i],B[i],1,-a[i]);
		}
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				if(a[i]<=a[j])Add(B[i],A[j],1,0);
			}
		}
		Add(S,s,m,0);Add(t,T,m,0);
		MCMF(S,T);printf("%d\n",-Cost);
	}
	return 0;
}