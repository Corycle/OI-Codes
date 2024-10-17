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
const int N=10005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[10];
map<int,int>E[N];
int n,m,tot,tmp[N],Ans[N];
struct edge{int x,y,l;}e[N*25];
struct Node{
	int fa[N],sum[N],st[N],top,ans;
	int Find(int x){return x==fa[x]?x:Find(fa[x]);}
	void Init(){for(int i=1;i<=n;i++)fa[i]=i,sum[i]=1;ans=n;}
	void Union(int x,int y){
		x=Find(x);y=Find(y);
		if(x==y)return;
		if(sum[x]>sum[y])swap(x,y);
		st[++top]=x;fa[x]=y;sum[y]+=sum[x];ans--;
	}
	void Reset(int t){
		while(top>t){
			int x=st[top--],y=fa[x];
			fa[x]=x;sum[y]-=sum[x];ans++;
		}
	}
}F;
struct Segment_Tree{
	vector<int>t[N*4];
	void Insert(int x,int y,int id,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){t[p].push_back(id);return;}
		int mid=(l+r)>>1;
		Insert(x,y,id,lson);Insert(x,y,id,rson);
	}
	void Solve(int p,int l,int r){
		int top=F.top;
		for(auto id:t[p])F.Union(e[id].x,e[id].y);
		if(l==r){Ans[l]=F.ans;F.Reset(top);return;}
		int mid=(l+r)>>1;Solve(lson);Solve(rson);F.Reset(top);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		E[x][y]=E[y][x]=++tot;
		e[tot]=(edge){x,y,1};
	}
	int Q=read()+1;
	for(int i=2;i<=Q;i++){
		scanf("%s",s);
		if(s[0]=='A'){
			int x=read(),y=read();
			E[x][y]=E[y][x]=++tot;
			e[tot]=(edge){x,y,i};
		}
		if(s[0]=='D'){
			int x=read(),y=read();
			int l=e[E[x][y]].l,r=i-1;
			tree.Insert(l,r,E[x][y],1,1,Q);
			e[E[x][y]].l=-1;
		}
		if(s[0]=='Q')tmp[++tmp[0]]=i;
	}
	for(int i=1;i<=tot;i++){
		if(e[i].l!=-1)tree.Insert(e[i].l,Q,i,1,1,Q);
	}
	F.Init();
	tree.Solve(1,1,Q);
	for(int i=1;i<=tmp[0];i++)printf("%d\n",Ans[tmp[i]]);
	return 0;
}