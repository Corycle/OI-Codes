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
const int N=1005;
const int M=N*20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
int h[N],cd[N],rd[N],dis[N];
struct Edge{int s,t,f1,f2;}e[M];
struct edge{int to,next,flow;}d[M];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
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
			if(dis[y]==-1&&d[i].flow){
				dis[y]=dis[x]+1;
				q.push(y);
			}
		}
	}
	return false;
}
int DFS(int x,int maxx,int t){
	int ans=0,dlt=0;
	if(x==t||!maxx)return maxx;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].flow&&dis[y]==dis[x]+1){
			dlt=DFS(y,min(maxx,d[i].flow),t);
			if(!dlt)dis[y]=-1;
			d[i].flow-=dlt;
			d[i^1].flow+=dlt;
			ans+=dlt;maxx-=dlt;
			if(!maxx)return ans;
		}
	}
	return ans;
}
int Dinic(int s,int t){
	int ans=0;
	while(BFS(s,t))ans+=DFS(s,inf,t);
	return ans;
}
int Build(int maxx){
	cnt=1;
	int S=0,T=n+1,sum=0;
	memset(h,0,sizeof(h));
	memset(cd,0,sizeof(cd));
	memset(rd,0,sizeof(rd));
	for(int i=1;i<=m;i++){
		if(e[i].f1<=maxx&&e[i].f2<=maxx){
			Add(e[i].s,e[i].t,1);
			cd[e[i].s]++;rd[e[i].t]++;
		}
		else if(e[i].f1<=maxx){cd[e[i].s]++;rd[e[i].t]++;}
		else if(e[i].f2<=maxx){cd[e[i].t]++;rd[e[i].s]++;}
	}
	for(int i=1;i<=n;i++){
		int dlt=abs(cd[i]-rd[i]);
		if(dlt&1)return -1;
		if(rd[i]<cd[i]){
			Add(S,i,dlt/2);
			sum+=dlt/2;
		}
		if(rd[i]>cd[i])Add(i,T,dlt/2);
	}
	return sum;
}
bool Check(int maxx){
	int S=0,T=n+1;
	int sum=Build(maxx);
	if(sum==-1)return false;
	if(sum!=Dinic(S,T))return false;
	return true;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	int l=0,r=0,ans=-1;
	for(int i=1;i<=m;i++){
		e[i].s=read();e[i].t=read();
		e[i].f1=read();e[i].f2=read();
		l=max(l,min(e[i].f1,e[i].f2));
		r=max(r,max(e[i].f1,e[i].f2));
	}
	while(l<=r){
		int mid=(l+r)>>1;
		if(Check(mid)){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	if(ans!=-1)printf("%d",ans);
	else printf("NIE");
	return 0;
}