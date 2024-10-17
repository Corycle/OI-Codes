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
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans,fa[N],val[N];
struct Edge{int x,y,a,b;}e[N];
struct Tree{int ch[2],fa,aux,rev,Max;};
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
bool cmp(Edge A,Edge B){return A.a!=B.a?A.a<B.a:A.b<B.b;}
struct Link_Cut_Tree{
	Tree t[N];
	void Pushup(int x){
		t[x].Max=x;
		if(val[t[x].Max]<val[t[t[x].ch[0]].Max])t[x].Max=t[t[x].ch[0]].Max;
		if(val[t[x].Max]<val[t[t[x].ch[1]].Max])t[x].Max=t[t[x].ch[1]].Max;
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
			t[t[x].ch[1]].aux=1;
			Pushup(x);y=x;x=t[x].fa;
		}
	}
	void Evert(int x){Access(x);Splay(x);t[x].rev^=1;}
	void Split(int x,int y){Evert(x);Access(y);Splay(y);}
	void Link(int x,int y){Split(x,y);t[x].fa=y;}
	void Cut(int x,int y){Split(x,y);t[x].fa=t[x].aux=t[y].ch[0]=0;Pushup(y);}
	int Ask(int x,int y){Split(x,y);return t[y].Max;}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		e[i].x=read();e[i].y=read();
		e[i].a=read();e[i].b=read();
	}
	Ans=inf;
	sort(e+1,e+m+1,cmp);
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=n+m;i++)tree.t[i].Max=i;
	for(int i=1;i<=m;i++){
		val[i+n]=e[i].b;
		if(Find(e[i].x)!=Find(e[i].y)){
			fa[Find(e[i].x)]=Find(e[i].y);
			tree.Link(e[i].x,i+n);
			tree.Link(e[i].y,i+n);
		}
		else{
			int p=tree.Ask(e[i].x,e[i].y)-n;
			if(e[p].b>e[i].b){
				tree.Cut(e[p].x,p+n);
				tree.Cut(e[p].y,p+n);
				tree.Link(e[i].x,i+n);
				tree.Link(e[i].y,i+n);
			}
			else continue;
		}
		if(Find(1)==Find(n))Ans=min(Ans,e[i].a+val[tree.Ask(1,n)]);
	}
	printf("%d",Ans!=inf?Ans:-1);
	return 0;
}