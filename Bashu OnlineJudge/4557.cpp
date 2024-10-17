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
const int N=500005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[10];
struct edge{int to,next;}d[N*2];
int n,m,cnt,tot,h[N],L[N],R[N],fa[N];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void DFS(int x,int Fa){L[x]=++tot;fa[x]=Fa;for(int i=h[x];i;i=d[i].next)if(d[i].to!=Fa)DFS(d[i].to,x);R[x]=tot;}
struct BIT{
	int c[N];
	int lowbit(int x){return x&(-x);}
	void Add(int x,int y){for(;x<=n;x+=lowbit(x))c[x]+=y;}
	int Ask(int x){int ans=0;for(;x>=1;x-=lowbit(x))ans+=c[x];return ans;}
	int Query(int l,int r){return Ask(r)-Ask(l-1);}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS(1,0);
	m=read()+n-1;
	for(int i=2;i<=n;i++){tree.Add(L[i],1);tree.Add(R[i]+1,-1);}
	while(m--){
		scanf("%s",s);
		if(s[0]=='A'){
			int x=read(),y=read();
			if(fa[x]==y){tree.Add(L[x],-1);tree.Add(R[x]+1,1);}
			if(fa[y]==x){tree.Add(L[y],-1);tree.Add(R[y]+1,1);}
		}
		if(s[0]=='W')printf("%d\n",tree.Ask(L[read()]));
	}
	return 0;
}