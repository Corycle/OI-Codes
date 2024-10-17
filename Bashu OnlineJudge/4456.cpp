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
const int N=300005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,tot;
char a[N],s[N],t[N];
int h[N],dep[N],sum[N],son[N],top[N];
int fa[N],id[N],pos[N],nxt[N],Ans[N];
struct edge{int to,next;char data;}d[N];
struct Node{int x,id,f;};
vector<Node>Q[N];
void Add(int x,int y,char z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
/*========Tree Chain Partition========*/
void DFS1(int x,int depth){
	dep[x]=depth;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;a[y]=d[i].data;
		DFS1(y,depth+1);sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
	}
}
void DFS2(int x,int tp){
	top[x]=tp;pos[id[x]=++tot]=x;
	if(son[x])DFS2(son[x],tp);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x]||y==son[x])continue;
		DFS2(y,y);
	}
}
int LCA(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x=fa[top[x]];
	}
	return dep[x]<dep[y]?x:y;
}
int Climb(int x,int depth){
	while(dep[top[x]]>depth)x=fa[top[x]];
	return pos[id[x]-dep[x]+depth];
}
/*========Operation========*/
int KMP(int x,int y,int z,int len){
	int L=dep[x]+dep[y]-dep[z]*2;
	if(L<len)return 0;
	int l=1,r=L,ans=0;
	while(x!=z){t[l++]=a[x];x=fa[x];}
	while(y!=z){t[r--]=a[y];y=fa[y];}
	for(int i=2,j=0;i<=len;i++){
		while(j&&s[i]!=s[j+1])j=nxt[j];
		if(s[i]==s[j+1])j++;
		nxt[i]=j;
	}
	for(int i=1,j=0;i<=L;i++){
		while(j&&(j==len||t[i]!=s[j+1]))j=nxt[j];
		if(t[i]==s[j+1])j++;
		ans+=(j==len);
	}
	for(int i=1;i<=L;i++)t[i]=0;
	return ans;
}
struct BIT{
	int n,c[N];
	int lowbit(int x){return x&(-x);}
	void Add(int x,int y){for(;x<=n;x+=lowbit(x))c[x]+=y;}
	int Ask(int x){int ans=0;for(;x>=1;x-=lowbit(x))ans+=c[x];return ans;}
};
struct AC_Tree{
	BIT bit;
	vector<int>G[N];
	int tot,dfn,root,L[N],R[N],Pos[N],fail[N],ch[N][26];
	void Prepare(){tot=root=1;}
	void Insert(int id,int len){
		int p=root;
		for(int i=1;i<=len;i++){
			int c=s[i]-'a';
			if(!ch[p][c])ch[p][c]=++tot;
			p=ch[p][c];
		}
		Pos[id]=p;
	}
	void DFS(int x){
		L[x]=++dfn;
		for(auto y:G[x])DFS(y);
		R[x]=dfn;
	}
	void Build(){
		queue<int>q;q.push(root);
		while(q.size()){
			int x=q.front();q.pop();
			for(int i=0;i<26;i++){
				int y=ch[x][i];
				if(!y)continue;
				int p=fail[x];q.push(y);
				while(p&&!ch[p][i])p=fail[p];
				fail[y]=(p?ch[p][i]:root);
			}
		}
		for(int i=2;i<=tot;i++)G[fail[i]].push_back(i);	
		DFS(root);bit.n=tot;
	}
	int Query(int x){
		return bit.Ask(R[Pos[x]])-bit.Ask(L[Pos[x]]-1);
	}
	int Son(int p,int c){
		while(p&&!ch[p][c])p=fail[p];
		return (p?ch[p][c]:root);
	}
}tree[2];
void Solve(int x,int p0,int p1){
	tree[0].bit.Add(tree[0].L[p0],1);
	tree[1].bit.Add(tree[1].L[p1],1);
	for(auto q:Q[x])Ans[q.id]+=tree[q.x].Query(q.id)*q.f;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to,c=d[i].data-'a';
		if(y==fa[x])continue;
		Solve(y,tree[0].Son(p0,c),tree[1].Son(p1,c));
	}
	tree[0].bit.Add(tree[0].L[p0],-1);
	tree[1].bit.Add(tree[1].L[p1],-1);
}
int main(){
//	freopen("4456.in","r",stdin);
//	freopen("4456.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		scanf("%s",s+1);
		Add(x,y,s[1]);
		Add(y,x,s[1]);
	}
	tree[0].Prepare();
	tree[1].Prepare();
	DFS1(1,1);DFS2(1,1);
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		scanf("%s",s+1);
		int z=LCA(x,y),len=strlen(s+1);
		int fx=Climb(x,min(dep[x],dep[z]+len-1));
		int fy=Climb(y,min(dep[y],dep[z]+len-1));
		Ans[i]+=KMP(fx,fy,z,len);
		tree[1].Insert(i,len);reverse(s+1,s+len+1);tree[0].Insert(i,len);
		if(x!=fx){Q[x].push_back((Node){0,i,1});Q[fx].push_back((Node){0,i,-1});}
		if(y!=fy){Q[y].push_back((Node){1,i,1});Q[fy].push_back((Node){1,i,-1});}
	}
	tree[0].Build();
	tree[1].Build();
	Solve(1,1,1);
	for(int i=1;i<=m;i++)printf("%d\n",Ans[i]);
	return 0;
}