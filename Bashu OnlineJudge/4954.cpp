/*====Corycle====*/
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
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
const double eps=1e-7;
const int N=100005;
const int M=105;
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
int n,m,cnt;
double dis[N],Ans;
int a[M][M],b[M][M];
int h[N],vis[N],pre[N];
struct edge{int to,next,flow;double cost;}d[N];
inline void Add(int x,int y,int f,double c){
	d[++cnt]=(edge){y,h[x],f,c};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0,-c};h[y]=cnt;
}
struct cmp{
	bool operator()(int x,int y){return dis[x]<dis[y];}
};
inline bool SPFA(int s,int t){
	for(register int i=1;i<=t;i++)dis[i]=-inf;
	priority_queue<int,vector<int>,cmp>q;
	q.push(s);dis[s]=0;
	while(q.size()){
		int x=q.top();q.pop();vis[x]=0;
		for(register int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].flow&&dis[y]<dis[x]+d[i].cost){
				dis[y]=dis[x]+d[i].cost;pre[y]=i;
				if(!vis[y]){vis[y]=1;q.push(y);}
			}
		}
	}
	return fabs(dis[t]+inf)>eps;
}
inline void Adjust(int s,int t){
	for(register int i=t;i!=s;i=d[pre[i]^1].to){
		d[pre[i]].flow--;
		d[pre[i]^1].flow++;
	}
	Ans+=dis[t];
}
inline void Edmonds_Karp(int s,int t){
	Ans=0;
	while(SPFA(s,t))Adjust(s,t);
}
inline bool Check(double x){
	cnt=1;
	int S=n*2+1,T=n*2+2;
	for(register int i=1;i<=T;i++)h[i]=0;
	for(register int i=1;i<=n;i++){
		Add(S,i,1,0);
		Add(i+n,T,1,0);
	}
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=n;j++){
			Add(i,j+n,1,a[i][j]-x*b[i][j]);
		}
	}
	Edmonds_Karp(S,T);
	return (Ans>0);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=n;j++)a[i][j]=read();
	}
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=n;j++)b[i][j]=read();
	}
	double l=0,r=1e4;
	while(l+eps<r){
		double mid=(l+r)/2;
		if(Check(mid))l=mid;
		else r=mid;
	}
	printf("%.6lf",l);
	return 0;
}