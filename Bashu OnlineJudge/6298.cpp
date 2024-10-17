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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,a,b,cnt,root;
int h[N],fa[N],rd[N],vis[N],sum[N],type[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS1(int x){
	sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;DFS1(y);
		sum[x]+=sum[y];
	}
}
void DFS2(int x,int t){
	type[x]=t;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		DFS2(y,t);
	}
}
void Solve(int t){
	queue<int>q;
	for(int i=1;i<=n;i++){
		if(type[i]==t&&!rd[i])q.push(i);
	}
	int num=0;
	while(q.size()){
		int x=q.front();q.pop();vis[x]=++num;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(type[y]==t){
				rd[y]--;
				if(!rd[y])q.push(y);
			}
		}
	}
}
int main(){
//	freopen("tom.in","r",stdin);
//	freopen("tom.out","w",stdout);
	n=read();a=read();b=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
		rd[x]++;rd[y]++;
	}
	DFS1(1);
	for(int i=1;i<=n;i++)rd[i]--;
	for(int i=1;i<=n;i++)if(sum[i]==a||sum[i]==b)root=i;
	if(!root){printf("-1");return 0;}
	if(sum[root]==a){for(int i=1;i<=n;i++)type[i]=-1;DFS2(root,1);}
	if(sum[root]==b){for(int i=1;i<=n;i++)type[i]=1;DFS2(root,-1);}
	Solve(1);Solve(-1);
	for(int i=1;i<=n;i++)printf("%d ",vis[i]*type[i]);
	return 0;
}