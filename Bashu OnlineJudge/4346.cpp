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
const double eps=1e-8;
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,sum;
int h[N],dis[N];
int a[N],b[N],c[N][N];
struct edge{
	int to,next;
	double flow;
}d[N*200];
void Add(int x,int y,double z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
}
bool P(double x){
	return abs(x)<eps;
}
bool BFS(int s,int t){
	queue<int>q;
	memset(dis,-1,sizeof(dis));
	q.push(s);dis[s]=0;
	while(q.size()){
		int x=q.front();q.pop();
		if(x==t)return true;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(!P(d[i].flow)&&dis[y]==-1){
				dis[y]=dis[x]+1;
				q.push(y);
			}
		}
	}
	return false;
}
double DFS(int x,double maxx,int t){
	double ans=0,dlt=0;
	if(x==t||P(maxx))return maxx;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(!P(d[i].flow)&&dis[y]==dis[x]+1){
			dlt=DFS(y,min(maxx,d[i].flow),t);
			if(P(dlt))dis[y]=-1;
			d[i].flow-=dlt;
			d[i^1].flow+=dlt;
			ans+=dlt;maxx-=dlt;
			if(P(maxx))return ans;
		}
	}
	return ans;
}
double Dinic(int s,int t){
	double ans=0;
	while(BFS(s,t))ans+=DFS(s,inf,t);
	return ans;
}
bool Check(double x){
	int S=0,T=n+m+1;cnt=1;
	memset(h,0,sizeof(h));
	for(int i=1;i<=n;i++)Add(m+i,T,a[i]);
	for(int i=1;i<=m;i++)Add(S,i,b[i]*x);
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			if(c[i][j])Add(i,j+m,inf);
		}
	}
	return P(Dinic(S,T)-sum);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++)b[i]=read();
	for(int i=1;i<=n;i++)sum+=a[i];
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			c[i][j]=read();
		}
	}
	double l=0,r=1e5;
	while(r-l>eps){
		double mid=(l+r)/2;
		if(Check(mid))r=mid;
		else l=mid;
	}
	printf("%.5lf",l);
	return 0;
}
