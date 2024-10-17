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
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
const int M=N*50;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,tot,len;
int h[N],b[N],rt[N],ans[N];
int p[N][35],dep[N],Max[M],id[M];
struct Tree{int l,r;}t[M];
struct ques{int l,r,v;}q[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS(int x,int depth){
	dep[x]=depth;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(dep[y])continue;
		DFS(y,depth+1);
		p[y][0]=x;
	}
}
void ST(){
	int k=(int)(log(n)/log(2));
	for(int j=1;j<=k;j++){
		for(int i=1;i<=n;i++){
			if(p[i][j-1]!=-1)p[i][j]=p[p[i][j-1]][j-1];
		}
	}
}
int lca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	int k=(int)(log(dep[x])/log(2));
	for(;k>=0;k--){
		if(dep[x]-(1<<k)>=dep[y])x=p[x][k];
	}
	if(x==y)return x;
	k=(int)(log(dep[x])/log(2));
	for(;k>=0;k--){
		if(p[x][k]!=p[y][k]){
			x=p[x][k];y=p[y][k];
		}
	}
	return p[x][0];
}
void Pushup(int x){
	int l=t[x].l,r=t[x].r;
	if(l&&r){
		if(Max[l]>Max[r]){Max[x]=Max[l];id[x]=id[l];}
		if(Max[l]<Max[r]){Max[x]=Max[r];id[x]=id[r];}
		if(Max[l]==Max[r]){Max[x]=Max[l];id[x]=min(id[l],id[r]);}
	}
	else if(l){Max[x]=Max[l];id[x]=id[l];}
	else if(r){Max[x]=Max[r];id[x]=id[r];}
}
int Merge(int x,int y){
	if(!x||!y)return x+y;
	Max[x]+=Max[y];
	t[x].l=Merge(t[x].l,t[y].l);
	t[x].r=Merge(t[x].r,t[y].r);
	Pushup(x);
	return x;
}
void Update(int &x,int y,int pos,int l,int r){
	if(!x)x=++tot;
	if(l==r){
		Max[x]+=y;
		id[x]=pos;
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)Update(t[x].l,y,pos,l,mid);
	if(pos>mid)Update(t[x].r,y,pos,mid+1,r);
	Pushup(x);
}
void Solve(int x){
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==p[x][0])continue;
		Solve(y);
		rt[x]=Merge(rt[x],rt[y]);
	}
	if(Max[rt[x]])ans[x]=id[rt[x]];
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	memset(p,-1,sizeof(p));
	DFS(1,1);ST();
	for(int i=1;i<=m;i++){
		q[i].l=read();
		q[i].r=read();
		q[i].v=b[i]=read();
	}
	sort(b+1,b+m+1);
	len=unique(b+1,b+m+1)-b-1;
	for(int i=1;i<=m;i++){
		q[i].v=lower_bound(b+1,b+len+1,q[i].v)-b;
		int x=lca(q[i].l,q[i].r);
		int y=p[x][0];
		Update(rt[x],-1,q[i].v,1,len);
		Update(rt[q[i].l],1,q[i].v,1,len);
		Update(rt[q[i].r],1,q[i].v,1,len);
		if(y)Update(rt[y],-1,q[i].v,1,len);
	}
	Solve(1);
	for(int i=1;i<=n;i++){
		printf("%d\n",b[ans[i]]);
	}
	return 0;
}