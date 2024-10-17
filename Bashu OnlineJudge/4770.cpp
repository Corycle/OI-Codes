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
const int M=1500005;
const int N=500005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,Ans;
int h[M],a[M],fa[M];
struct edge{int to,next;}d[M];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
struct Tree{int ch[2],id[3],fa,rev,aux,tag,sum,val;};
struct Link_Cut_Tree{
	Tree t[N];
	void Update(int x,int addv){
		t[x].tag+=addv;
		t[x].sum+=addv;
		t[x].val=(t[x].sum>=2);
		swap(t[x].id[1],t[x].id[2]);
	}
	void Pushup(int x){
		t[x].id[1]=t[t[x].ch[1]].id[1];t[x].id[2]=t[t[x].ch[1]].id[2];
		if(!t[x].id[1]){if(t[x].sum!=1)t[x].id[1]=x;else t[x].id[1]=t[t[x].ch[0]].id[1];}
		if(!t[x].id[2]){if(t[x].sum!=2)t[x].id[2]=x;else t[x].id[2]=t[t[x].ch[0]].id[2];}
	}
	void Pushdown(int x){
		if(t[x].tag){
			if(t[x].ch[0])Update(t[x].ch[0],t[x].tag);
			if(t[x].ch[1])Update(t[x].ch[1],t[x].tag);
			t[x].tag=0;
		}
	}
	void Rotate(int x){
		int y=t[x].fa;int z=t[y].fa;
		int l=(x!=t[y].ch[0]),r=l^1;
		if(t[y].aux){
			if(y==t[z].ch[0])t[z].ch[0]=x;
			else t[z].ch[1]=x;
		}
		else{t[x].aux=0;t[y].aux=1;}
		t[x].fa=z;t[y].fa=x;
		t[t[x].ch[r]].fa=y;
		t[y].ch[l]=t[x].ch[r];
		t[x].ch[r]=y;
		Pushup(y);Pushup(x);
	}
	void Splay(int x){
		Pushdown(x);
		while(t[x].aux){
			int y=t[x].fa,z=t[y].fa;
			if(t[y].aux)Pushdown(z);
			Pushdown(y);Pushdown(x);
			if(t[y].aux){
				if((x==t[y].ch[0])^(y==t[z].ch[0]))Rotate(x);
				else Rotate(y);
			}
			Rotate(x);
		}
	}
	void Access(int x){
		int y=0;
		while(x){
			Splay(x);
			t[t[x].ch[1]].aux=0;
			t[x].ch[1]=y;
			t[t[x].ch[1]].aux=1;
			Pushup(x);y=x;x=t[x].fa;
		}
	}
	void Change(int x,int addv){
		Splay(x);
		Update(t[x].ch[1],addv);
		Pushup(t[x].ch[1]);
		t[x].sum+=addv;
		t[x].val=(t[x].sum>=2);
		Pushup(x);
	}
}tree;
int DFS(int x){
	if(x>n)return a[x];
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		tree.t[x].sum+=DFS(y);
	}
	return a[x]=(tree.t[x].sum>=2);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		int x=read(),y=read(),z=read();
		Add(i,x);Add(i,y);Add(i,z);
		fa[x]=fa[y]=fa[z]=i;
	}
	for(int i=n+1;i<=n*3+1;i++)a[i]=read();
	for(int i=1;i<=n;i++)tree.t[i].fa=fa[i];
	Ans=DFS(1);
	m=read();
	while(m--){
		int x=read();
		int t=a[x];a[x]^=1;
		int addv=(t?-1:1);x=fa[x];
		tree.Access(x);tree.Splay(x);
		int p=tree.t[x].id[t?2:1];
		if(p)tree.Change(p,addv);
		else{tree.Update(x,addv);Ans^=1;}
		printf("%d\n",Ans);
	}
	return 0;
}