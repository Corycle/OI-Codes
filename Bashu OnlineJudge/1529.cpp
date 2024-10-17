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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,S,T,cnt1=1,cnt2=1;
int h1[N],h2[N],q[N];
int dis[N],f1[N],f2[N];
struct edge{
	int to,next,data;
}d1[N*20],d2[N*20];
void Add(int x,int y,int z){
	d1[++cnt1]=(edge){y,h1[x],z};h1[x]=cnt1;
	d2[++cnt2]=(edge){x,h2[y],z};h2[y]=cnt2;
}
bool BFS(){
	memset(dis,-1,sizeof(dis));
	int l=1,r=1;
	dis[S]=0;
	q[1]=S;
	while(l<=r){
		int x=q[l++];
		if(x==T)return true;
		for(int i=h1[x];i;i=d1[i].next){
			int y=d1[i].to;
			if(dis[y]==-1&&d1[i].data){
				dis[y]=dis[x]+1;
				q[++r]=y;
			}
		}
	}
	return false;
}
int DFS(int x,int maxx){
	int ans=0,dlt=0;
	if(x==T||!maxx)return maxx;
	for(int i=h1[x];i;i=d1[i].next){
		int y=d1[i].to;
		if(d1[i].data&&dis[y]==dis[x]+1){
			dlt=DFS(y,min(maxx,d1[i].data));
			if(dlt==0)dis[y]=-1;
			d1[i].data-=dlt;
			d1[i^1].data+=dlt;
			ans+=dlt;maxx-=dlt;
			if(!maxx)return ans;
		}
	}
	return ans;
}
int Dinic(){
	int ans=0;
	while(BFS())ans+=DFS(S,inf);
	return ans;
}
void DFS1(int x){
	f1[x]=1;
	for(int i=h1[x];i;i=d1[i].next){
		int y=d1[i].to;
		if(!f1[y]&&d1[i].data){
			DFS1(y);
		}
	}
}
void DFS2(int x){
	f2[x]=1;
	for(int i=h2[x];i;i=d2[i].next){
		int y=d2[i].to;
		if(!f2[y]&&d2[i].data){
			DFS2(y);
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	S=read();T=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		Add(x,y,z);
		Add(y,x,z);
	}
	Dinic();
	int ans=0;
	for(int i=1;i<=cnt1;i++){
		d2[i].data=d1[i].data;
	}
	DFS1(S);DFS2(T);
	for(int i=1;i<=n;i++){
		if(f1[i]||f2[i])ans++;
	}
	if(ans!=n)printf("AMBIGUOUS");
	else printf("UNIQUE");
	return 0;
}