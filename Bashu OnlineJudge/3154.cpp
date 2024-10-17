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
const int N=305;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt=1;
int Max[N][N],Min[N][N],Ans[N][N];
int h[N],dis[N],la[N],lb[N],down[N];
struct edge{
	int to,next,flow,type;
}d[N*50];
void Add(int x,int y,int z,int t){
	d[++cnt]=(edge){y,h[x],z,t};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0,t};h[y]=cnt;
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
			if(d[i].flow&&dis[y]==-1){
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
void Build1(int x,int y,int z){
	if(x==0&&y==0)for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)Min[i][j]=max(Min[i][j],z);
	else if(x==0)for(int i=1;i<=n;i++)Min[i][y]=max(Min[i][y],z);
	else if(y==0)for(int i=1;i<=m;i++)Min[x][i]=max(Min[x][i],z);
	else Min[x][y]=max(Min[x][y],z);
}
void Build2(int x,int y,int z){
	if(x==0&&y==0)for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)Max[i][j]=min(Max[i][j],z);
	else if(x==0)for(int i=1;i<=n;i++)Max[i][y]=min(Max[i][y],z);
	else if(y==0)for(int i=1;i<=m;i++)Max[x][i]=min(Max[x][i],z);
	else Max[x][y]=min(Max[x][y],z);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int S,T,s,t;
	int Case=read();
	while(Case--){
		n=read();m=read();
		memset(h,0,sizeof(h));
		memset(Min,0,sizeof(Min));
		memset(Max,0x3f,sizeof(Max));
		memset(down,0,sizeof(down));
		s=0;t=n+m+1;cnt=1;
		for(int i=1;i<=n;i++)la[i]=read();
		for(int i=1;i<=m;i++)lb[i]=read();
		int KFC=read();
		while(KFC--){
			int x=read(),y=read();
			char op[1];scanf("%s",op);
			int z=read();
			if(op[0]=='>')Build1(x,y,z+1);
			if(op[0]=='<')Build2(x,y,z-1);
			if(op[0]=='='){
				Build1(x,y,z);
				Build2(x,y,z);
			}
		}
		bool flag=false;
		int sum1=0,sum2=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(Max[i][j]<Min[i][j])flag=true;
				else{
					int dlt=Max[i][j]-Min[i][j];
					Add(i,j+n,dlt,1);
					down[i]-=Min[i][j];
					down[j+n]+=Min[i][j];
				}
				if(flag)break;
			}
			if(flag)break;
		}
		for(int i=1;i<=n;i++){
			sum1+=la[i];
//			Add(s,i,0,1);
			down[s]-=la[i];
			down[i]+=la[i];
		}
		for(int i=1;i<=m;i++){
			sum2+=lb[i];
//			Add(i+n,t,0,1);
			down[i+n]-=lb[i];
			down[t]+=lb[i];
		}
		if(sum1!=sum2||flag){
			printf("IMPOSSIBLE\n\n");
			continue;
		}
		S=t+1;T=S+1;
		int sum=0;
		for(int i=s;i<=t;i++){
			if(down[i]>0){
				Add(S,i,down[i],0);
				sum+=down[i];
			}
			if(down[i]<0)Add(i,T,-down[i],0);
		}
		Add(t,s,inf,0);
		if(Dinic(S,T)!=sum)printf("IMPOSSIBLE\n\n");
		else{
			for(int x=1;x<=n;x++){
				for(int i=h[x];i;i=d[i].next){
					int y=d[i].to;
					if(n+1<=y&&y<=n+m)Ans[x][y-n]=Min[x][y-n]+d[i^1].flow;
				}
				for(int y=1;y<=m;y++)printf("%d ",Ans[x][y]);
				printf("\n");
			}
			printf("\n");
		}
	}
	return 0;
}