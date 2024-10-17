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
const int N=300005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,tot,Max;
int a[N],b[N],c[N],h[N],fa[N];
int dep[N],sum[N],son[N],vis[N],ans[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};h[x]=cnt;
	d[++cnt]=(edge){x,h[y]};h[y]=cnt;
}
void DFS(int x,int depth){
	sum[x]=1;
	dep[x]=depth;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;
		DFS(y,depth+1);
		sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
	}
}
void Update(int x,int addv){
	c[a[x]]+=addv;
	if(addv==1&&c[a[x]]>=c[Max]){
		if(c[a[x]]>c[Max])Max=a[x];
		else Max=min(Max,a[x]);
	}
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x]||vis[y])continue;
		Update(y,addv);
	}
}
int DSU(int x,int flag){
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x]||y==son[x])continue;
		DSU(y,0);
	}
	if(son[x]){
		DSU(son[x],1);
		vis[son[x]]=1;
	}
	Update(x,1);ans[x]=Max;
	if(son[x])vis[son[x]]=0;
	if(!flag){
		Update(x,-1);
		Max=0;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int size=40<<20;//40M
//	__asm__ ("movl %0,%%esp\n"::"r"((char*)malloc(size)+size));//调试用这个
	__asm__ ("movq %0,%%rsp\n"::"r"((char*)malloc(size)+size));//提交用这个
	n=read();
	for(int i=1;i<=n;i++)a[i]=b[i]=read();
	for(int i=2;i<=n;i++)Add(read(),read());
	sort(b+1,b+n+1);
	tot=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(b+1,b+n+1,a[i])-b;
	}
	DFS(1,1);DSU(1,0);
	for(int i=1;i<=n;i++){
		printf("%d\n",b[ans[i]]);
	}
	exit(0);
	return 0;
}