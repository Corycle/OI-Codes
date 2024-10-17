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
const int N=205;
const int M=N*N;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
int h[N],cd[N],rd[N],dis[N];
struct edge{
	int to,next,flow;
}d[M];
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
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int S,T;
	int Case=read();
	while(Case--){
		n=read();m=read();
		cnt=1;S=0;T=n+1;
		memset(h,0,sizeof(h));
		memset(cd,0,sizeof(cd));
		memset(rd,0,sizeof(rd));
		for(int i=1;i<=m;i++){
			int x=read(),y=read(),z=read();
			if(z==0)Add(x,y,1);//如果di=1，表示该街道是一条单行道（从xi到yi），否则它是一个双行道。
			cd[x]++;rd[y]++;
		}
		int sum=0;
		bool bj=true;
		for(int i=1;i<=n;i++){
			int dlt=abs(cd[i]-rd[i]);
			if(dlt&1)bj=false;
			if(rd[i]<cd[i]){
				Add(S,i,dlt/2);
				sum+=dlt/2;
			}
			if(rd[i]>cd[i])Add(i,T,dlt/2);
		}
		if(!bj){
			printf("impossible\n");
			continue;
		}
		if(sum!=Dinic(S,T))printf("impossible\n");
		else printf("possible\n");
	}
	return 0;
}
