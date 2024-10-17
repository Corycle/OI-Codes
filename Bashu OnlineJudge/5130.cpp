/*====Corycle====*/
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
int n,K,type,cnt,Ans;
int h[N],dep[N],fa[N],vst[N],vis[N];
struct edge{int to,next;}d[N*2];
struct Node{int id,depth;}P[N];
bool cmp(Node A,Node B){
	return A.depth>B.depth;
}
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS(int x,int depth){
	dep[x]=depth;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;DFS(y,depth+1);
	}
}
void Solve(int x,int dis){
	vst[x]=vis[x]=1;
	if(dis>0){
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(!vis[y])Solve(y,dis-1);
		}
	}
	vis[x]=0;
}
int main(){
//	freopen("general.in","r",stdin);
//	freopen("general.out","w",stdout);
	n=read();K=read();type=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS(1,1);
	for(int i=1;i<=n;i++){
		P[i]=(Node){i,dep[i]};
	}
	sort(P+1,P+n+1,cmp);
	for(int i=1;i<=n;i++){
		if(!vst[P[i].id]){
			Solve(P[i].id,K*2);
			Ans++;
		}
	}
	printf("%d\n",Ans);
	return 0;
}