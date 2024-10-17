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
const int N=10005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,p,cnt=1;
int h[N],dis[N];
struct edge{
	int to,next;
	double flow;
	double data;
}d[N*50];
void Add(int x,int y,double z){
	d[++cnt]=(edge){y,h[x],z,z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0,0};h[y]=cnt;
}
bool BFS(int s,int t){
	memset(dis,-1,sizeof(dis));
	queue<int>q;
	q.push(s);
	dis[s]=0;
	while(q.size()){
		int x=q.front();
		q.pop();
		if(x==t)return true;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].flow>eps&&dis[y]==-1){
				dis[y]=dis[x]+1;
				q.push(y);
			}
		}
	}
	return false;
}
double DFS(int x,double maxx,int t){
	double ans=0,dlt=0;
	if(x==t||maxx<eps)return maxx;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].flow>eps&&dis[y]==dis[x]+1){
			dlt=DFS(y,min(maxx,d[i].flow),t);
			if(!dlt)dis[y]=-1;
			d[i].flow-=dlt;
			d[i^1].flow+=dlt;
			ans+=dlt;maxx-=dlt;
			if(maxx<eps)return ans;
		}
	}
	return ans;
}
double Dinic(int s,int t){
	double ans=0;
	while(BFS(s,t))ans+=DFS(s,inf,t);
	return ans;
}
void Build(double x){
	for(int i=2;i<=cnt;i+=2){
		d[i].flow=min(d[i].data,x);
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();p=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		Add(x,y,z);
	}
	double sum=Dinic(1,n);
	printf("%.0lf\n",sum+eps);
	double l=0,r=sum,ans=0;
	while(r-l>eps){
		double mid=(l+r)/2.0;
		Build(mid);
		double now=Dinic(1,n);
		if(abs(now-sum)<eps){
			ans=mid;
			r=mid;
		}
		else l=mid;
	}
	Build(ans);
	sum=Dinic(1,n);
	for(int i=2;i<=cnt;i+=2){
		ans=max(ans,d[i].flow);
	}
	printf("%.6lf",ans*p);
	return 0;
}