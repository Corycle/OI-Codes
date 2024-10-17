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
const int N=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
int h[N],down[N],dis[N];
struct edge{
	int to,next,flow,type;
}d[N*50];
void Add(int x,int y,int f,int t){
	d[++cnt]=(edge){y,h[x],f,t};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0,-t};h[y]=cnt;
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
	int s,t,S,T;
	while(1){
		n=read();m=read();
		if(n+m==0)break;
		s=0;t=n+1;cnt=1;
		memset(h,0,sizeof(h));
		memset(down,0,sizeof(down));
		for(int i=1;i<=m;i++){
			char sx[N],sy[N];
			scanf("%s%s",sx+1,sy+1);
			int x=0,y=0,z=read();
			int l1=strlen(sx+1);
			int l2=strlen(sy+1);
			if(sx[1]=='+')x=s;
			else for(int j=1;j<=l1;j++)x=x*10+sx[j]-'0';
			if(sy[1]=='-')y=t;
			else for(int j=1;j<=l2;j++)y=y*10+sy[j]-'0';
			Add(x,y,inf-z,1);
			down[x]-=z;down[y]+=z;
		}
		S=t+1;T=S+1;
		int sum=0;
		for(int i=s;i<=t;i++){
			if(down[i]>0){
				sum+=down[i];
				Add(S,i,down[i],0);
			}
			if(down[i]<0)Add(i,T,-down[i],0);
		}
		Add(t,s,inf,0);
		if(sum==Dinic(S,T)){
			int ans=d[cnt].flow;
			for(int i=2;i<=cnt;i++){
				if(d[i].type==0)d[i].flow=0;
			}
			ans-=Dinic(t,s);
			printf("%d\n",ans);
		}
		else printf("impossible\n");
	}
	return 0;
}