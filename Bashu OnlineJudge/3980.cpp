/*====Corycle====*/
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
const int N=1505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot,cnt;
int A[N],B[N],h[N],f[N];
int H[N],dis[N],vis[N],Ans[N];
struct edge{int to,next,flow;}d[N*N];
struct Node{int a,b,c,id,num;}P[N];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
}
bool cmp(Node x,Node y){
	return x.c<y.c;
}
bool BFS(int s,int t){
	for(int i=1;i<=tot;i++)dis[i]=-1;
	queue<int>q;q.push(s);dis[s]=0;
	while(q.size()){
		int x=q.front();q.pop();
		if(x==t)return true;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].flow&&dis[y]==-1){
				dis[y]=dis[x]+1;q.push(y);
			}
		}
	}
	return false;
}
int DFS(int x,int maxx,int t){
	if(x==t||!maxx)return maxx;
	int ans=0;
	for(int &i=H[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].flow&&dis[y]==dis[x]+1){
			int dlt=DFS(y,min(d[i].flow,maxx),t);
			if(!dlt)dis[y]=-1;
			d[i].flow-=dlt;
			d[i^1].flow+=dlt;
			maxx-=dlt;ans+=dlt;
			if(!maxx)return ans;
		}
	}
	return ans;
}
int Dinic(int s,int t){
	int Flow=0;
	while(BFS(s,t)){
		for(int i=1;i<=tot;i++)H[i]=h[i];
		Flow+=DFS(s,inf,t);
	}
	return Flow;
}
bool Check(int s,int t){
	for(int i=1;i<=tot;i++)vis[i]=0;
	queue<int>q;q.push(s);vis[s]=1;
	while(q.size()){
		int x=q.front();q.pop();
		if(x==t)return true;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].flow&&!vis[y]){
				vis[y]=1;q.push(y);
			}
		}
	}
	return false;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		n=read();
		int Max=0;tot=0;cnt=1;
		memset(h,0,sizeof(h));
		for(int i=1;i<=n;i++)P[i].a=read();
		for(int i=1;i<=n;i++)P[i].b=read();
		for(int i=1;i<=n;i++)P[i].c=read();
		for(int i=1;i<=n;i++)P[i].id=i;
		for(int i=1;i<=n;i++)f[i]=1;
		for(int i=1;i<=n;i++){
			for(int j=1;j<i;j++){
				if(P[j].a<P[i].a)f[i]=max(f[i],f[j]+1);
			}
			Max=max(Max,f[i]);
		}
		int S=++tot,T=++tot;
		for(int i=1;i<=n;i++){
			A[i]=++tot;B[i]=++tot;
			if(f[i]==1)Add(S,A[i],inf);
			if(f[i]==Max)Add(B[i],T,inf);
			for(int j=1;j<i;j++){
				if(P[j].a<P[i].a&&f[i]==f[j]+1)Add(B[j],A[i],inf);
			}
			Add(A[i],B[i],P[i].b);
			P[i].num=cnt;
		}
		Ans[0]=0;
		int sum=Dinic(S,T);
		sort(P+1,P+n+1,cmp);
		for(int i=1;i<=n;i++){
			int k=P[i].id;
			if(Check(A[k],B[k]))continue;
			Ans[++Ans[0]]=k;
			Dinic(T,B[k]);Dinic(A[k],S);
			d[P[i].num].flow=d[P[i].num^1].flow=0;
		}
		sort(Ans+1,Ans+Ans[0]+1);
		printf("%d %d\n",sum,Ans[0]);
		for(int i=1;i<=Ans[0];i++)printf("%d ",Ans[i]);
		printf("\n");
	}
	return 0;
}