#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
#define Point pair<int,int>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1000005;
const int Dlt=30000;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
Point P[N];
int n,cnt=1;
map<Point,int>num,val;
int dx[6]={0,0,1,-1,1,-1};
int dy[6]={1,-1,0,0,1,-1};
int h[N],A[N],B[N],flag[N],dis[N];
struct edge{int to,next,flow;}d[N*5];
void Add(int x,int y,int z){
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
			if(d[i].flow&&dis[y]==-1){
				dis[y]=dis[x]+1;
				q.push(y);
			}
		}
	}
	return false;
}
int DFS(int x,int maxx,int t){
	int ans=0;
	if(x==t||!maxx)return maxx;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].flow&&dis[y]==dis[x]+1){
			int dlt=DFS(y,min(maxx,d[i].flow),t);
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
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	int ans=0;
	for(int i=1;i<=n;i++){
		int x=read(),y=read(),z=read();
		int C=read()*((x+y+z+Dlt)%3==0?11:10);
		P[i]=make_pair(x-z,y-z);ans+=C;
		if(!num[P[i]]){
			num[P[i]]=i;
			val[P[i]]=C;
		}
		else{
			val[P[i]]+=C;
			flag[i]=1;
		}
		A[i]=i;B[i]=i+n;
	}
	int S=n*2+1,T=n*2+2;
	for(int i=1;i<=n;i++){
		if(flag[i])continue;
		if((P[i].first+P[i].second+Dlt)%3==0)Add(B[i],A[i],val[P[i]]);
		if((P[i].first+P[i].second+Dlt)%3==1)Add(S,A[i],val[P[i]]);
		if((P[i].first+P[i].second+Dlt)%3==2)Add(B[i],T,val[P[i]]);
	}
	for(int i=1;i<=n;i++){
		if(flag[i])continue;
		for(int j=0;j<6;j++){
			int x=P[i].first+dx[j],y=P[i].second+dy[j];
			int id=num[(Point){x,y}];
			if(!id)continue;
			if((x+y+Dlt)%3==0&&(P[i].first+P[i].second+Dlt)%3==1)Add(A[i],B[id],inf);
			if((x+y+Dlt)%3==2&&(P[i].first+P[i].second+Dlt)%3==0)Add(A[i],B[id],inf);
		}
	}
	ans-=Dinic(S,T);
	printf("%d.%d",ans/10,ans%10);
	return 0;
}