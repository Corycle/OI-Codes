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
const int N=10005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,tot;
int h[N],A[N],B[N],f1[N],f2[N],dis[N];
struct edge{int to,next,flow;}d[N];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
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
	for(int i=h[x];i;i=d[i].next){
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
	int ans=0;
	while(BFS(s,t))ans+=DFS(s,inf,t);
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		n=read();tot=0;cnt=1;
		memset(h,0,sizeof(h));
		for(int i=1;i<=n;i++)A[i]=++tot;//students
		for(int i=1;i<=n;i++)B[i]=++tot;//beds
		for(int i=1;i<=n;i++)f1[i]=read();
		for(int i=1;i<=n;i++)f2[i]=read();
		int S=++tot,T=++tot,num=0;
		for(int i=1;i<=n;i++){
			Add(A[i],B[i],1);
			if(f1[i])Add(B[i],T,1);//have beds
			if(!f1[i]||!f2[i]){Add(S,A[i],1);num++;}//need beds
			for(int j=1;j<=n;j++)if(read())Add(A[i],B[j],1);
		}
		if(Dinic(S,T)==num)printf("^_^\n");
		else printf("T_T\n");
	}
	return 0;
}