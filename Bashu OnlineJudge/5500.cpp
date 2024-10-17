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
const int M=100005;
const int N=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,h[N],dis[N];
struct Node{int x,y,r,w;}A[N],B[N];
struct edge{int to,next,flow;}d[M];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
}
ll Sqr(ll x){return x*x;}
bool Check(int x,int y){
	return Sqr(A[x].x-B[y].x)+Sqr(A[x].y-B[y].y)<=Sqr(A[x].r);
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
			int dlt=DFS(y,min(maxx,d[i].flow),t);
			if(!dlt)dis[y]=-1;
			d[i].flow-=dlt;
			d[i^1].flow+=dlt;
			maxx-=dlt;ans+=dlt;
			if(!maxx)return ans;
		}
	}
	return ans;
}
int Dinic(int x,int y){
	int ans=0;
	while(BFS(x,y))ans+=DFS(x,inf,y);
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int Case=read();
	while(Case--){
		n=read();m=read();cnt=1;memset(h,0,sizeof(h));
		for(int i=1;i<=n;i++){A[i].x=read();A[i].y=read();A[i].w=read();A[i].r=read();}
		for(int i=1;i<=m;i++){B[i].x=read();B[i].y=read();B[i].w=read();}
		int Max=A[1].w,Sum=0,S=n+m+1,T=n+m+2;
		for(int j=1;j<=m;j++){
			if(Check(1,j)){Max+=B[j].w;continue;}
			int flag=0;
			for(int i=2;i<=n;i++){
				if(Check(i,j)){flag=1;Add(i,j+n,inf);}
			}
			if(flag){Add(j+n,T,B[j].w);Sum+=B[j].w;}
		}
		int flag=0;
		for(int i=1;i<=n;i++){
			if(Max-A[i].w<0){flag=1;break;}
			Add(S,i,Max-A[i].w);
		}
		if(flag)puts("qaq");
		else if(Dinic(S,T)!=Sum)puts("qaq");
		else puts("ZQC! ZQC!");
	}
	return 0;
}