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
int n,m;
struct Link_Cut_Tree{
	struct Tree{int fa,rev,sum,data,aux,ch[2];}t[N];
	void Pushup(int x){
		t[x].sum=t[t[x].ch[0]].sum^t[t[x].ch[1]].sum^t[x].data;
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
		else{t[y].aux=1;t[x].aux=0;}
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
	int Find(int x){Access(x);Splay(x);while(t[x].ch[0]){Pushdown(x);x=t[x].ch[0];}Splay(x);return x;}
	void Evert(int x){Access(x);Splay(x);t[x].rev^=1;}
	void Split(int x,int y){Evert(x);Access(y);Splay(y);}
	void Link(int x,int y){if(Find(x)!=Find(y)){Evert(x);t[x].fa=y;}}
	void Cut(int x,int y){
		if(Find(x)==Find(y)){
			Split(x,y);
			if(t[x].fa==y&&!t[x].ch[1]){
				t[x].fa=t[x].aux=t[y].ch[0]=0;Pushup(y);
			}
		}
	}
//	void Cut(int x,int y){
//		Find(x);Find(y);if(t[x].fa!=y&&t[y].fa!=x)return;
//		Split(x,y);t[x].fa=t[x].aux=t[y].ch[0]=0;Pushup(y);
//	}
	void Change(int x,int y){Access(x);Splay(x);t[x].data=y;Pushup(x);}
	void Query(int x,int y){Split(x,y);printf("%d\n",t[y].sum);}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		tree.t[i].data=tree.t[i].sum=read();
	}
	for(int i=1;i<=m;i++){
		int op=read(),x=read(),y=read();
		if(op==0)tree.Query(x,y);
		if(op==1)tree.Link(x,y);
		if(op==2)tree.Cut(x,y);
		if(op==3)tree.Change(x,y);
	}
	return 0;
}