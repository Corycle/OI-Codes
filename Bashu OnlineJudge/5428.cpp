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
const int N=400005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[10];
int n,m,tot,a[N],fa[N],pos[N];
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
struct Tree{int ch[2],fa,rev,aux,Min,sum,data;};
struct Edge{int x,y;}e[N];
struct Link_Cut_Tree{
	Tree t[N];
	void Pushup(int x){
		t[x].Min=x;
		t[x].sum=t[t[x].ch[0]].sum+t[t[x].ch[1]].sum+t[x].data;
		if(a[t[x].Min]>a[t[t[x].ch[0]].Min])t[x].Min=t[t[x].ch[0]].Min;
		if(a[t[x].Min]>a[t[t[x].ch[1]].Min])t[x].Min=t[t[x].ch[1]].Min;
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
		int l=(t[y].ch[0]!=x),r=l^1;
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
	void Evert(int x){Access(x);Splay(x);t[x].rev^=1;}
	void Change(int x,int y){Evert(x);t[x].data=y;Pushup(x);}
	void Split(int x,int y){Evert(x);Access(y);Splay(y);}
	void Link(int x,int y){Evert(x);t[x].fa=y;}
	void Cut(int x,int y){Split(x,y);t[x].fa=t[x].aux=t[y].ch[0]=0;Pushup(y);}
	int Ask(int x,int y){Split(x,y);return t[y].sum;}
	int Min(int x,int y){Split(x,y);return t[y].Min;}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();tot=n;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=0;i<=n;i++)a[tree.t[i].Min=i]=inf;
	for(int i=1;i<=m;i++){
		scanf("%s",s);
		if(s[0]=='f'){
			int id=read();
			pos[id]=++tot;
			int x=e[tot].x=read()+1;
			int y=e[tot].y=read()+1;
			a[tree.t[tot].Min=tot]=read();
			tree.t[tot].data=read();
			if(Find(x)==Find(y)){
				int z=tree.Min(x,y);
				if(a[z]>a[tot])continue;
				tree.Cut(e[z].x,z);
				tree.Cut(e[z].y,z);
			}
			fa[Find(x)]=Find(y);
			tree.Link(x,tot);
			tree.Link(y,tot);
		}
		if(s[0]=='c'){
			int x=read(),y=read();
			tree.Change(pos[x],y);
		}
		if(s[0]=='m'){
			int x=read()+1,y=read()+1;
			if(Find(x)!=Find(y))puts("-1");
			else printf("%d\n",tree.Ask(x,y));
		}
	}
	return 0;
}