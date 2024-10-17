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
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
int n,m,tot;
int ch[N][2],fa[N],id[N],pos[N],dep[N],sum[N],son[N],top[N];
struct Tree{
	int c[N];
	int lowbit(int x){return x&(-x);}
	void Add(int x,int y){for(;x<=n;x+=lowbit(x))c[x]+=y;}
	int Ask(int x){int ans=0;for(;x>=1;x-=lowbit(x))ans+=c[x];return ans;}
	int Query(int l,int r){return Ask(r)-Ask(l-1);}
}tree;
void DFS1(int x,int depth){
	dep[x]=depth;sum[x]=1;
	for(int i=0;i<2;i++){
		int y=ch[x][i];
		if(!y)continue;fa[y]=x;
		DFS1(y,depth+1);sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
	}
}
void DFS2(int x,int tp){
	top[x]=tp;pos[id[x]=++tot]=x;
	if(son[x])DFS2(son[x],tp);
	for(int i=0;i<2;i++){
		int y=ch[x][i];
		if(!y||y==son[x])continue;
		DFS2(y,y);
	}
}
int Size(int x){return x?tree.Query(id[x],id[x]+sum[x]-1):0;}
int Climb(int x,int depth){
	while(dep[top[x]]>depth)x=fa[top[x]];
	return pos[id[x]-(dep[x]-depth)];
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){ch[i][0]=read();ch[i][1]=read();}
	DFS1(1,1);DFS2(1,1);
	for(int i=1;i<=n;i++){Ans+=son[i];tree.Add(i,1);}
	printf("%lld\n",Ans);
	m=read();
	while(m--){
		int x=read(),Root=1;tree.Add(id[x],-1);
		while(1){
			int l=dep[Root]+1,r=dep[x],depth=0;
			while(l<=r){
				int mid=(l+r)>>1;
				if(Size(Climb(x,mid))<=Size(Root)/2){depth=mid;r=mid-1;}
				else l=mid+1;
			}
			if(!depth)break;
			int x1=Climb(x,depth),x2=ch[fa[x1]][(x1!=ch[fa[x1]][0])^1];
			if(son[fa[x1]]==x1){
				if(Size(x1)<Size(x2)){Ans+=x2-x1;son[fa[x1]]=x2;}
				else if(!Size(x1)&&!Size(x2)){Ans-=x1;son[fa[x1]]=0;}
			}
			Root=x1;
		}
		printf("%lld\n",Ans);
	}
	return 0;
}