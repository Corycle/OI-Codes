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
const int M=26;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
char s[N];
int n,m,tot,Root[N],val[N];
int id[N],sum[N],dep[N],son[N],top[N];
struct SAM{
	vector<int>G[N];
	int tot=1,lst=1,root=1;
	int ch[N][M],fa[N],len[N],pos1[N],pos2[N];
	void Insert(int num,int id){
		int x=lst,fx=++tot;len[fx]=len[x]+1;
		while(x&&!ch[x][num]){ch[x][num]=fx;x=fa[x];}
		if(!x)fa[fx]=root;
		else{
			int y=ch[x][num];
			if(len[y]==len[x]+1)fa[fx]=y;
			else{
				int fy=++tot;len[fy]=len[x]+1;
				fa[fy]=fa[y];fa[y]=fa[fx]=fy;
				memcpy(ch[fy],ch[y],sizeof(ch[fy]));
				while(x&&ch[x][num]==y){ch[x][num]=fy;x=fa[x];}
			}
		}
		lst=fx;pos1[pos2[fx]=id]=fx;
	}
	void Build(){for(int i=2;i<=tot;i++)G[fa[i]].push_back(i);}
}sam1,sam2;
void DFS1(int x,int depth){
	dep[x]=depth;sum[x]=1;
	for(auto y:sam2.G[x]){
		DFS1(y,depth+1);sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
	}
}
void DFS2(int x,int tp){
	top[x]=tp;id[x]=++tot;
	val[tot]=sam2.len[x]-sam2.len[sam2.fa[x]];
	if(son[x])DFS2(son[x],tp);
	for(auto y:sam2.G[x]){
		if(y!=son[x])DFS2(y,y);
	}
}
struct Tree{int l,r,tag;ll sum;};
struct Segment_Tree{
	int tot;
	Tree t[N*40];
	void Insert(int x,int y,int &p,int l,int r){
		if(!p)p=++tot;if(t[p].tag)return;
		if(x<=l&&r<=y){t[p].tag=1;t[p].sum=val[r]-val[l-1];return;}
		int mid=(l+r)>>1;
		if(x<=mid)Insert(x,y,t[p].l,l,mid);
		if(y>mid)Insert(x,y,t[p].r,mid+1,r);
		t[p].sum=t[t[p].l].sum+t[t[p].r].sum;
		t[p].tag=t[t[p].l].tag&t[t[p].r].tag;
	}
	int Merge(int x,int y){
		if(!x||!y)return x|y;
		if(t[x].tag)return x;
		if(t[y].tag)return y;
		t[x].l=Merge(t[x].l,t[y].l);
		t[x].r=Merge(t[x].r,t[y].r);
		t[x].sum=t[t[x].l].sum+t[t[x].r].sum;
		t[x].tag=t[t[x].l].tag&t[t[x].r].tag;
		return x;
	}
}tree;
void Insert(int x,int pos){
	if(pos>=n+2)return;
	if(pos==n+1)tree.Insert(id[1],id[1],Root[x],1,tot);
	else{
		int p=sam2.pos1[pos];
		while(p){
			tree.Insert(id[top[p]],id[p],Root[x],1,tot);
			p=sam2.fa[top[p]];
		}
	}
}
void Solve(int x){
	if(x==1||sam1.pos2[x])Insert(x,sam1.pos2[x]+2);
	for(auto y:sam1.G[x]){Solve(y);Root[x]=tree.Merge(Root[x],Root[y]);}
	Ans+=1ll*(sam1.len[x]-sam1.len[sam1.fa[x]])*(tree.t[Root[x]].sum+1);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	scanf("%s",s+1);n=strlen(s+1);
	for(int i=1;i<=n;i++)sam1.Insert(s[i]-'a',i);sam1.Build();
	for(int i=n;i>=1;i--)sam2.Insert(s[i]-'a',i);sam2.Build();
	sam1.len[0]=sam2.len[0]=-1;DFS1(1,1);DFS2(1,1);
	for(int i=1;i<=tot;i++)val[i]+=val[i-1];
	Solve(1);
	printf("%lld",Ans);
	return 0;
}