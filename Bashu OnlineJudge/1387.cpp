/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<vector>
#include<cstdio>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,h[N],fa[N];
struct edge{int to,next;}d[N*2];
struct Tree{int ch[2],fa,rev,aux,sum,data;};
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
struct Link_Cut_Tree{
	int tot;Tree t[N];
	void Pushup(int x){
		t[x].sum=t[t[x].ch[0]].sum+t[t[x].ch[1]].sum+t[x].data;
	}
	void Pushdown(int x){
		if(t[x].rev){
			t[x].rev=0;
			t[t[x].ch[0]].rev^=1;
			t[t[x].ch[1]].rev^=1;
			swap(t[x].ch[0],t[x].ch[1]);
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
			t[y].aux=1;
			t[y].fa=x;
			Pushup(x);
			y=x;x=t[x].fa;
		}
	}
	void Evert(int x){Access(x);Splay(x);t[x].rev^=1;}
	void Change(int x,int y){Evert(x);t[x].data=y;Pushup(x);}
	void Split(int x,int y){Evert(x);Access(y);Splay(y);}
	void Link(int x,int y){Evert(x);t[x].fa=y;}
	void Cut(int x,int y){Split(x,y);t[y].ch[0]=t[x].fa=t[x].aux=0;Pushup(y);}
	void Ask(int x,int y){Split(x,y);printf("%d\n",t[y].sum);}
}tree;
void DFS(int x){
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;DFS(y);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
		tree.Link(x,y);
	}
	for(int i=1;i<=n;i++)tree.Change(i,read());
	DFS(1);
	char op[5];
	while(m--){
		scanf("%s",op);
		int x=read(),y=read();
		if(op[0]=='S')tree.Ask(x,y);
		if(op[0]=='C')tree.Change(x,y);
		if(op[0]=='F'){tree.Cut(x,fa[x]);tree.Link(x,fa[x]=y);}
		if(op[0]=='A'){tree.Change(++n,y);tree.Link(n,fa[n]=x);}
	}
	return 0;
}