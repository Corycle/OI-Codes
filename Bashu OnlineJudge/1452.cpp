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
const int inf=0x3f3f3f3f;
const int N=40005;
const int M=205;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
struct Point{int x,y;};
int n,m,a[M][M],b[M][M],Ans[N][2];
int id(int x,int y){return (x-1)*n+y;}
struct Union_Basis{
	int top,Ans,st[N],fa[N],sum[N];
	int Find(int x){return x==fa[x]?x:Find(fa[x]);}
	void Init(){Ans=top=0;for(int i=1;i<=n*n;i++){fa[i]=i;sum[i]=1;}}
	void Union(int x,int y){
		x=Find(x);y=Find(y);
		if(x!=y){Ans--;if(sum[x]>sum[y])swap(x,y);fa[x]=y;sum[y]+=sum[x];st[++top]=x;}
	}
	void Reset(int tmp,int ans){
		Ans=ans;
		while(top>tmp){int x=st[top--];sum[fa[x]]-=sum[x];fa[x]=x;}
	}
}F;
struct Segment_Tree{
	vector<Point>t[2][N*4];
	void Update(int x,int y,int c){
		a[x][y]=c;F.Ans++;
		for(int i=0;i<4;i++){
			int fx=x+dx[i],fy=y+dy[i];
			if(a[fx][fy]==c)F.Union(id(x,y),id(fx,fy));
		}
	}
	void Update(int x,int y,int c,Point P,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){t[c][p].push_back(P);return;}
		int mid=(l+r)>>1;Update(x,y,c,P,lson);Update(x,y,c,P,rson);
	}
	void Solve(int c,int p,int l,int r){
		int top=F.top,tmp=F.Ans;for(auto P:t[c][p])Update(P.x,P.y,c);
		if(l==r){Ans[l][c]=F.Ans;F.Reset(top,tmp);for(auto P:t[c][p])a[P.x][P.y]=-1;return;}
		int mid=(l+r)>>1;Solve(c,lson);Solve(c,rson);F.Reset(top,tmp);for(auto P:t[c][p])a[P.x][P.y]=-1;
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){a[i][j]=read();b[i][j]=0;}
	m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		tree.Update(b[x][y],i-1,a[x][y],(Point){x,y},1,0,m);
		b[x][y]=i;a[x][y]^=1;
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)tree.Update(b[i][j],m,a[i][j],(Point){i,j},1,0,m);
	F.Init();memset(a,-1,sizeof(a));tree.Solve(0,1,0,m);
	F.Init();memset(a,-1,sizeof(a));tree.Solve(1,1,0,m);
	for(int i=1;i<=m;i++)printf("%d %d\n",Ans[i][1],Ans[i][0]);
	return 0;
}