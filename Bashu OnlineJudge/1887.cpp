#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
using namespace std;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int S,n,N,cnt=0,dis[30005],vis[30005],tot[30005],h[30005];
struct node{
	int to,next,v;
}e[30005];
void AddEdge(int x,int y,int v){
	e[++cnt]=(node){y,h[x],v};
	h[x]=cnt;
}
bool SPFA(){
	int i,j,k;
	memset(dis,0x7f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	queue<int>Q;
	Q.push(S);
	dis[S]=0;
	while(Q.size()){
		int x=Q.front();
		vis[x]=false;
		Q.pop();
		for(int p=h[x];p;p=e[p].next){
			int y=e[p].to;
			if(dis[y]>dis[x]+e[p].v){
				dis[y]=dis[x]+e[p].v;
				tot[y]++;
				if(tot[y]==N+1){
					return false;
				}
				if(!vis[y]){
					vis[y]=true;
					Q.push(y);
				}
			}
		}
	}
	for(i=0;i<=N-1;i++)if(dis[i]>(1<<29))return false;
	return true;
}
int main(){
	int i,j,k;
	int n=read(),a0=read(),b0=read(),l0=read(),a1=read(),b1=read(),l1=read();
	N=n+2;
	S=n+1;
	for(i=1;i<=n;i++){
		AddEdge(i,i-1,0);
		AddEdge(i-1,i,1);
	}
	AddEdge(S,0,0);
	for(i=l0;i<=n;i++){
		AddEdge(i,i-l0,-(l0-b0));
		AddEdge(i-l0,i,+(l0-a0));
	}
	for(i=l1;i<=n;i++){
		AddEdge(i,i-l1,-(a1));
		AddEdge(i-l1,i,+(b1));
	}
	if(SPFA()){
		cout<<dis[n]-dis[0]<<"\n";
	}
	else cout<<"-1\n";
//	for(i=0;i<=n;i++)cout<<dis[i]<<" ";cout<<endl;
	return 0;
}