/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const double eps=1e-5;
const int M=100005;
const int N=705;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
double Ans,len[N],Dis[N];
int h[N],rd[N],st[N],t1[N],t2[N],deg[N],dis[N];
struct edge{int to,next;double data;}e[M],d[M*10];
struct Edge{int x,y,t,s;}E[M];
void Add1(int x,int y,double z){
	e[++cnt]=(edge){y,h[x],z};h[x]=cnt;
}
void Add2(int x,int y,double z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
}
bool BFS(int s,int t){
	memset(dis,-1,sizeof(dis));
	queue<int>q;q.push(s);dis[s]=0;
	while(q.size()){
		int x=q.front();q.pop();
		if(x==t)return true;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].data>eps&&dis[y]==-1){
				dis[y]=dis[x]+1;q.push(y);
			}
		}
	}
	return false;
}
double DFS(int x,double maxx,int t){
	if(x==t||maxx<eps)return maxx;
	double ans=0;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].data>eps&&dis[y]==dis[x]+1){
			double dlt=DFS(y,min(d[i].data,maxx),t);
			d[i].data-=dlt;
			d[i^1].data+=dlt;
			maxx-=dlt;ans+=dlt;
			if(maxx<eps)return ans;
		}
	}
	return ans;
}
double Dinic(int s,int t){
	double Flow=0;
	while(BFS(s,t))Flow+=DFS(s,inf,t);
	return Flow;
}
void Solve(){
	int S=n,T=n+1;cnt=1;
	memset(h,0,sizeof(h));
	int m1=read(),n1=read();
	for(int i=1;i<=n1;i++){
		if(i&1)Add2(S,i,len[i]);
		else Add2(i,T,len[i]);
	}
	for(int i=1;i<=m1;i++){
		int x=read(),y=read();
		Add2(x,y,inf);
	}
	Ans=Dinic(S,T);
}
void Check(double Ans){
	cnt=0;
	memset(h,0,sizeof(h));
	memcpy(rd,deg,sizeof(rd));
	for(int i=1;i<=m;i++){
		Add1(E[i].x,E[i].y,E[i].t-Ans*E[i].s);
	}
	queue<int>q;
	for(int i=1;i<=n;i++)Dis[i]=inf;Dis[n]=0;
	for(int i=1;i<=n;i++)if(!rd[i])q.push(i);
	while(q.size()){
		int x=q.front();q.pop();
		for(int i=h[x];i;i=e[i].next){
			int y=e[i].to;
			Dis[y]=min(Dis[y],Dis[x]+e[i].data);
			rd[y]--;if(!rd[y])q.push(y);
		}
	}
}
void Divide(int ql,int qr,double l,double r){
	if(ql>qr)return;
	if(r-l<=eps){
		for(int i=ql;i<=qr;i++)len[st[i]]=l;
		return;
	}
	int L=0,R=0,k=ql;
	double mid=(l+r)/2;Check(mid);
	for(int i=ql;i<=qr;i++){
		if(Dis[st[i]]<eps)t1[++L]=st[i];
		else t2[++R]=st[i];
	}
	for(int i=1;i<=L;i++)st[k++]=t1[i];
	for(int i=1;i<=R;i++)st[k++]=t2[i];
	Divide(ql,ql+L-1,l,mid);
	Divide(ql+L,qr,mid,r);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		int t=read(),s=read();
		E[i]=(Edge){x,y,t,s};
		deg[y]++;
	}
	for(int i=1;i<=n;i++)st[i]=i;
	Divide(1,n,0,20);
	for(int i=1;i<=n;i++){
		if(len[i]>=10.1)len[i]=inf;
	}
	Solve();
	if(Ans>=1e8)printf("-1");
	else printf("%.1lf",Ans);
	return 0;
}