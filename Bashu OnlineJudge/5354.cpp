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
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const ll inf=0x7f7f7f7f7f7f7f7f;
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll a[N],f[N],g[N];
int n,m,cnt,tot,flag;
int h[N],fa[N],st[N],ed[N];
int dep[N],pos[N],sum[N],son[N],top[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS1(int x,int depth){
	dep[x]=depth;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;fa[y]=x;
		DFS1(y,depth+1);sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
	}
}
void DFS2(int x,int tp){
	top[x]=tp;st[x]=ed[x]=++tot;pos[tot]=x;
	if(son[x]){DFS2(son[x],tp);ed[x]=ed[son[x]];}
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x]||y==son[x])continue;
		DFS2(y,y);g[x]+=f[y];
	}
	if(!son[x]){f[x]=a[x];g[x]=inf;}
	else f[x]=min(a[x],g[x]+f[son[x]]);
}
struct Matrix{
	ll a[2][2];
	void Init(){memset(a,0x7f,sizeof(a));}
	friend Matrix operator*(Matrix A,Matrix B){
		Matrix C;C.Init();
		for(int i=0;i<2;i++){
			for(int j=0;j<2;j++){
				for(int k=0;k<2;k++){
					C.a[i][j]=min(C.a[i][j],A.a[i][k]+B.a[k][j]);
				}
			}
		}
		return C;
	}
}Ans;
struct Segment_Tree{
	Matrix t[N*4];
	Matrix Prepare(int x){
		Matrix tmp;
		tmp.a[0][0]=g[pos[x]];
		tmp.a[0][1]=a[pos[x]];
		tmp.a[1][0]=0;
		tmp.a[1][1]=0;
		return tmp;
	}
	void Build(int p,int l,int r){
		if(l==r){t[p]=Prepare(l);return;}
		int mid=(l+r)>>1;
		Build(lson);Build(rson);
		t[p]=t[p<<1]*t[p<<1|1];
	}
	void Update(int x,int p,int l,int r){
		if(x<l||x>r)return;
		if(l==r){t[p]=Prepare(l);return;}
		int mid=(l+r)>>1;
		Update(x,lson);Update(x,rson);
		t[p]=t[p<<1]*t[p<<1|1];
	}
	void Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){
			if(!flag){Ans=t[p];flag=1;}
			else Ans=Ans*t[p];
			return;
		}
		int mid=(l+r)>>1;
		Query(x,y,lson);Query(x,y,rson);
	}
}tree;
ll Query(int x){
	Ans.Init();flag=0;
	tree.Query(st[x],ed[x],1,1,n);
	return min(Ans.a[0][0],Ans.a[0][1]);
}
void Change(int x,int addv){
	a[x]+=addv;
	while(x){
		g[fa[top[x]]]-=Query(top[x]);
		tree.Update(st[x],1,1,n);
		g[fa[top[x]]]+=Query(top[x]);
		x=fa[top[x]];
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS1(1,1);DFS2(1,1);
	tree.Build(1,1,n);
	char op[5];
	m=read();
	while(m--){
		scanf("%s",op);int x=read();
		if(op[0]=='C')Change(x,read());
		if(op[0]=='Q')printf("%lld\n",Query(x));
	}
	return 0;
}