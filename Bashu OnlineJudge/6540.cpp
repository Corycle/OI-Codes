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
const int Mod=1e9+7;
const int N=400005;
const int M=26;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
vector<int>G[N];
int n,m,tot,Ans,Answer;
int fa[N],id[N],pos[N],Pos[N],son[N],sum[N],top[N],dep[N];
int mod(int x){return x>=Mod?x-Mod:x;}
void DFS1(int x,int depth){
	dep[x]=depth;sum[x]=1;
	for(auto y:G[x]){
		DFS1(y,depth+1);sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
	}
}
void DFS2(int x,int tp){
	top[x]=tp;pos[id[x]=++tot]=x;
	if(son[x])DFS2(son[x],tp);
	for(auto y:G[x]){
		if(y==son[x])continue;
		DFS2(y,y);
	}
}
struct SAM{
	int root=1,lst=1,tot=1;
	int ch[N][M],len[N];
	void Insert(int num){
		int x=lst,fx=++tot;len[fx]=len[x]+1;
		while(x&&!ch[x][num]){ch[x][num]=fx;x=fa[x];}
		if(!x)fa[fx]=root;
		else{
			int y=ch[x][num];
			if(len[y]==len[x]+1)fa[fx]=y;
			else{
				int fy=++tot;len[fy]=len[x]+1;
				fa[fy]=fa[y];fa[y]=fa[fx]=fy;
				memcpy(ch[fy],ch[y],sizeof(ch[y]));
				while(x&&ch[x][num]==y){ch[x][num]=fy;x=fa[x];}
			}
		}
		lst=fx;
	}
	void Build(){for(int i=2;i<=tot;i++)G[fa[i]].push_back(i);}
}sam;
struct Tree{ll sum,tag,val;};
struct Segment_Tree{
	Tree t[N*4];
	void update(int p,int x){
		t[p].tag=mod(t[p].tag+x);
		t[p].sum=mod(t[p].sum+1ll*x*t[p].val%Mod);
	}
	void Pushdown(int p){
		if(t[p].tag){
			update(p<<1,t[p].tag);
			update(p<<1|1,t[p].tag);
			t[p].tag=0;
		}
	}
	void Build(int p,int l,int r){
		if(l==r){t[p].val=sam.len[pos[l]]-sam.len[fa[pos[l]]];return;}
		int mid=(l+r)>>1;Build(lson);Build(rson);
		t[p].val=mod(t[p<<1].val+t[p<<1|1].val);
	}
	void Update(int x,int y,int z,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,z);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,z,lson);Update(x,y,z,rson);
		t[p].sum=mod(t[p<<1].sum+t[p<<1|1].sum);
	}
	int Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].sum;
		int mid=(l+r)>>1;Pushdown(p);
		return mod(Query(x,y,lson)+Query(x,y,rson));
	}
}tree;
void Update(int x){
	while(x){
		tree.Update(id[top[x]],id[x],1,1,1,tot);
		x=fa[top[x]];
	}
}
int Query(int x){
	int ans=0;
	while(x){
		ans=mod(ans+tree.Query(id[top[x]],id[x],1,1,tot));
		x=fa[top[x]];
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	scanf("%s",s+1);
	for(int i=1;i<=n;i++){
		sam.Insert(s[i]-'a');
		Pos[i]=sam.lst;
	}
	sam.Build();
	DFS1(1,1);DFS2(1,1);
	tree.Build(1,1,tot);
	for(int i=1;i<=n;i++){
		Ans=mod(Ans+Query(Pos[i]));
		Answer=mod(Answer+Ans);
		printf("%d\n",Answer);
		Update(Pos[i]);
	}
	return 0;
}