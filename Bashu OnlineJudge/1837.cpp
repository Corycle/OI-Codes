/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
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
int n,m,fa[N],d1[N],d2[N];
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
struct Link_Cut_Tree{
	struct Tree{int ch[2],fa,aux,rev,sum;}t[N];
	void Pushup(int x){
		t[x].sum=t[t[x].ch[0]].sum+t[t[x].ch[1]].sum+1;
	}
	void Pushdown(int x){
		if(t[x].rev){
			t[x].rev^=1;
			t[t[x].ch[0]].rev^=1;
			t[t[x].ch[1]].rev^=1;
			swap(t[x].ch[0],t[x].ch[1]);
		}
	}
	void Rotate(int x){
		int y=t[x].fa;int z=t[y].fa;
		int l=(x!=t[y].ch[0]);int r=l^1;
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
			int y=t[x].fa;int z=t[y].fa;
			if(t[y].aux)Pushdown(z);
			Pushdown(y);Pushdown(x);
			if(t[y].aux){
				if((y==t[z].ch[0])^(x==t[y].ch[0]))Rotate(x);
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
	void Split(int x,int y){Evert(x);Access(y);Splay(y);}
	int Dist(int x,int y){Split(x,y);return t[y].sum-1;}
	void Link(int x,int y){
		Evert(x);Evert(y);t[x].fa=y;
		x=Find(x);y=Find(y);fa[x]=y;
		int sx=d1[x],tx=d2[x],sy=d1[y],ty=d2[y],Max=-inf;
		if(Dist(sx,tx)>Max){Max=Dist(sx,tx);d1[y]=sx;d2[y]=tx;}//sx->tx
		if(Dist(sy,ty)>Max){Max=Dist(sy,ty);d1[y]=sy;d2[y]=ty;}//sy->ty
		if(Dist(sx,ty)>Max){Max=Dist(sx,ty);d1[y]=sx;d2[y]=ty;}//sx->ty
		if(Dist(sy,tx)>Max){Max=Dist(sy,tx);d1[y]=sy;d2[y]=tx;}//sy->tx
		if(Dist(sx,sy)>Max){Max=Dist(sx,sy);d1[y]=sx;d2[y]=sy;}//sx->sy
		if(Dist(tx,ty)>Max){Max=Dist(tx,ty);d1[y]=tx;d2[y]=ty;}//tx->ty
	}
}tree;
int main(){
//	freopen("hike.in","r",stdin);
//	freopen("hike.out","w",stdout);
	m=read();
	for(int i=1;i<=m;i++){
		tree.t[i].sum=1;
		fa[i]=d1[i]=d2[i]=i;
	}
	char op[5];
	while(m--){
		scanf("%s",op);
		if(op[0]=='B'){
			int x=read();n++;
			if(x!=-1)tree.Link(x,n);
		}
		if(op[0]=='Q'){
			int x=read();
			int ans=-inf,fx=Find(x);
			ans=max(ans,tree.Dist(x,d1[fx]));
			ans=max(ans,tree.Dist(x,d2[fx]));
			printf("%d\n",ans);
		}
	}
	return 0;
}