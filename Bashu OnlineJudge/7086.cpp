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
#include<set>
#define ll long long
#define set_it set<Node>::iterator
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
int a[N],h[N],fa[N],prt[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
int Find(int x){return x==prt[x]?x:prt[x]=Find(prt[x]);}
struct Node{
	int x,c;
	friend bool operator<(Node A,Node B){return A.c!=B.c?A.c<B.c:A.x<B.x;}
}P[N];
set<Node>F[N];
void Merge(int x,int y){
	x=Find(x);y=Find(y);prt[Find(y)]=Find(x);
	if(F[x].size()<F[y].size())swap(F[x],F[y]);
	for(set_it p=F[y].begin();p!=F[y].end();p++)F[x].insert(*p);
	F[y].clear();
}
void DFS(int x){
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;DFS(y);
		if(a[x]==a[y])Merge(x,y);
		else F[x].insert((Node){y,a[y]});
	}
}
int main(){
//	freopen("tree.in","r",stdin);
//	freopen("tree.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<n;i++){int x=read(),y=read();Add(x,y);Add(y,x);}
	for(int i=1;i<=n;i++){a[i]=read();prt[i]=i;}
	DFS(1);
	while(m--){
		int op=read();
		if(op==1){
			int x=Find(read()),c=read(),tot=0;
			if(fa[x])F[Find(fa[x])].erase((Node){x,a[x]});a[x]=c;
			for(set_it p=F[x].lower_bound((Node){0,c});p!=F[x].end();p++){
				if((*p).c!=c)break;
				P[++tot]=(*p);
			}
			for(int i=1;i<=tot;i++)F[x].erase(P[i]);
			for(int i=1;i<=tot;i++)Merge(x,P[i].x);
			if(fa[x]){
				if(a[Find(fa[x])]==c)Merge(fa[x],x);
				else F[Find(fa[x])].insert((Node){x,c});
			}
		}
		if(op==2)cout<<a[Find(read())]<<'\n';
	}
	return 0;
}