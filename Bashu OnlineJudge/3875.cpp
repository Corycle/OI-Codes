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
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,a[N],h[N],cnt,dep[N];
int prt[N],p[N][25],root[N],tot;
struct tree{
	int ch[2],s;
}t[N*20];
struct edge{
	int to,next;
}d[N*2];
void init(){
	cnt=0;
	memset(t,0,sizeof(t));
	memset(d,0,sizeof(d));
	memset(h,0,sizeof(h));
	memset(p,-1,sizeof(p));
}
void Add_edge(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
int Insert(int x,int data){
	int rt=++tot;
	int y=rt;
	for(int i=15;i>=0;i--){
		t[y].ch[0]=t[x].ch[0];
		t[y].ch[1]=t[x].ch[1];
		t[y].s=t[x].s+1;
		int c=(data>>i)&1;
		x=t[x].ch[c];
		y=t[y].ch[c]=++tot;
	}
	t[y].s=t[x].s+1;
	return rt;
}
void dfs(int x,int depth){
	dep[x]=depth;
	root[x]=Insert(root[prt[x]],a[x]);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(dep[y])continue;
		prt[y]=x;
		dfs(y,depth+1);
	}
}
void ST(){
	int k=(int)(log(n)/log(2));
	for(int i=1;i<=n;i++)p[i][0]=prt[i];
	for(int j=1;j<=k;j++){
		for(int i=1;i<=n;i++){
			if(p[i][j-1]!=-1)p[i][j]=p[p[i][j-1]][j-1];
		}
	}
}
int lca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int k=log2(n);k>=0;k--){
		if(dep[x]-(1<<k)>=dep[y])x=p[x][k];
	}
	if(x==y)return x;
	for(int k=log2(n);k>=0;k--){
		if(p[x][k]!=p[y][k]){
			x=p[x][k];
			y=p[y][k];
		}
	}
	return p[x][0];
}
int Ask(int x,int y,int z,int data){
	int ans=0;
	for(int i=15;i>=0;i--){
		int c=(data>>i)&1;
		if(t[t[x].ch[!c]].s+t[t[y].ch[!c]].s-2*t[t[z].ch[!c]].s>0){
			//(s[ch[x][!t]]-s[ch[z][!t]])+(s[ch[y][!t]]-s[ch[z][!t]])
			x=t[x].ch[!c];y=t[y].ch[!c];z=t[z].ch[!c];
			ans+=(1<<i);
		}
		else{
			x=t[x].ch[c];y=t[y].ch[c];z=t[z].ch[c];
		}
	}
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	while(scanf("%d%d",&n,&m)!=EOF){
		init();
		for(int i=1;i<=n;i++)a[i]=read();
		for(int i=1;i<=n-1;i++){
			int x=read(),y=read();
			Add_edge(x,y);
			Add_edge(y,x);
		}
		dfs(1,1);
		ST();
		while(m--){
			int x=read(),y=read(),data=read();
			int z=lca(x,y);
			int ans=Ask(root[x],root[y],root[z],data);
			printf("%d\n",max(ans,data^a[z]));
		}
	}
	return 0;
}