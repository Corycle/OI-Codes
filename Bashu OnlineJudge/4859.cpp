/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<cstring>
#include<complex>
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
const int M=(1<<20)+5;
const int N=5e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
queue<int>q;
int n,m,tot,cnt;
bool vis1[N],vis2[M];
int a[N],h[N+M],dis1[N],dis2[M];
struct edge{int to,next;}d[N+M];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void DFS(int x,int dist){
	if(vis2[x])return;
	vis2[x]=1;dis2[x]=dist;
	for(int i=0;i<20;i++){
		if((x>>i)&1)DFS(x^(1<<i),dist);
	}
	x+=n+1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(!vis1[y]){vis1[y]=1;dis1[y]=dist;q.push(y);}
	}
}
void BFS(){
	q.push(1);vis1[1]=1;
	while(q.size()){
		int x=q.front();q.pop();
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(y>n)DFS(y-n-1,dis1[x]+1);
			else if(!vis1[y]){vis1[y]=1;dis1[y]=dis1[x]+1;q.push(y);}
		}
	}
}
int main(){
//	freopen("walk.in","r",stdin);
//	freopen("walk.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){a[i]=read();Add(i,a[i]+n+1);Add(a[i]+n+1,i);}
	for(int i=1;i<=m;i++){int x=read(),y=read();Add(x,y);}
	BFS();
	for(int i=1;i<=n;i++)printf("%d\n",vis1[i]?dis1[i]:-1);
	return 0;
}