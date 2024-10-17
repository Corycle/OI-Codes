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
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Q,type;
int fa[N],Root[N];
struct Edge{int x,y;}E[N];
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
struct Tree{int ch[2],fa,aux,rev,id,Min;};
struct Link_Cut_Tree{
	Tree t[N*2];
	void Pushup(int x){
		t[x].Min=t[x].id;
		if(t[x].ch[0])t[x].Min=min(t[x].Min,t[t[x].ch[0]].Min);
		if(t[x].ch[1])t[x].Min=min(t[x].Min,t[t[x].ch[1]].Min);
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
		if(t[y].aux)t[z].ch[y!=t[z].ch[0]]=x;
		else{t[x].aux=0;t[y].aux=1;}
		t[x].fa=z;t[y].fa=x;t[t[x].ch[r]].fa=y;
		t[y].ch[l]=t[x].ch[r];t[x].ch[r]=y;
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
	void Cut(int x,int y){Split(x,y);t[y].ch[0]=t[x].aux=t[x].fa=0;Pushup(y);}
	int Ask(int x,int y){Split(x,y);return t[y].Min;}
	void Init(){
		for(int i=1;i<=n;i++)t[i].id=t[i].Min=m+1;
		for(int i=1;i<=m;i++)t[i+n].id=t[i+n].Min=i;
	}
}lct;
struct Node{int l,r,sum;};
struct Segment_Tree{
	int tot;
	Node t[N*M];
	void Insert(int &x,int y,int pos,int l,int r){
		x=++tot;t[x]=t[y];t[x].sum++;
		if(l==r)return;int mid=(l+r)>>1;
		if(pos<=mid)Insert(t[x].l,t[y].l,pos,l,mid);
		if(pos>mid)Insert(t[x].r,t[y].r,pos,mid+1,r);
	}
	int Query(int x,int y,int ql,int qr,int l,int r){
		if(qr<l||ql>r)return 0;
		if(ql<=l&&r<=qr)return t[y].sum-t[x].sum;
		int mid=(l+r)>>1;
		return Query(t[x].l,t[y].l,ql,qr,l,mid)+Query(t[x].r,t[y].r,ql,qr,mid+1,r);
	}
}tree;
void Link(int p){lct.Link(E[p].x,p+n);lct.Link(E[p].y,p+n);}
void Cut(int p){lct.Cut(E[p].x,p+n);lct.Cut(E[p].y,p+n);}
int Update(int x,int y,int id){
	if(Find(x)!=Find(y)){
		fa[Find(x)]=Find(y);
		Link(id);
		return 0;
	}
	int p=lct.Ask(x,y);
	Cut(p);Link(id);
	return p;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Q=read();type=read();
	lct.Init();
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		E[i].x=read();E[i].y=read();
		if(E[i].x==E[i].y)Root[i]=Root[i-1];
		else{
			int id=Update(E[i].x,E[i].y,i);
			tree.Insert(Root[i],Root[i-1],id,0,m);
		}
	}
	int Ans=0;
	while(Q--){
		int l=read()^(Ans*type);
		int r=read()^(Ans*type);
		if(l>r)swap(l,r);
		printf("%d\n",Ans=n-tree.Query(Root[l-1],Root[r],0,l-1,0,m));
	}
	return 0;
}