#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=5e4+5;
const int M=10;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,p,cnt,Ans;
int a[M],b[M],h[N];
int vis[N],vst[N],dis[M][N];
struct edge{
	int to,next,data;
}d[N*2];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
void SPFA(int num){
	memset(vis,0,sizeof(vis));
	int s=a[num];vis[s]=1;
	queue<int>q;q.push(s);
	dis[num][s]=0;
	while(q.size()){
		int x=q.front();
		q.pop();vis[x]=0;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(dis[num][y]>dis[num][x]+d[i].data){
				dis[num][y]=dis[num][x]+d[i].data;
				if(!vis[y]){vis[y]=1;q.push(y);}
			}
		}
	}
}
void DFS(int x){
	if(x==p+1){
		int sum=0;
		for(int i=2;i<=p;i++){
			sum+=dis[b[i-1]][a[b[i]]];
		}
		for(int i=1;i<=n;i++){
			if(vst[i])continue;
			Ans=min(Ans,sum+dis[b[1]][i]+dis[b[p]][i]);
		}
		return;
	}
	for(int i=1;i<=p;i++){
		if(!vis[i]){
			b[x]=i;
			vis[i]=1;
			DFS(x+1);
			vis[i]=0;
			b[x]=0;
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();p=read();
	for(int i=1;i<=p;i++){
		a[i]=read();
		vst[a[i]]=1;
	}
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	memset(dis,0x3f,sizeof(dis));
	for(int i=1;i<=p;i++)SPFA(i);
	memset(vis,0,sizeof(vis));
	Ans=inf;DFS(1);
	printf("%d",Ans);
	return 0;
}