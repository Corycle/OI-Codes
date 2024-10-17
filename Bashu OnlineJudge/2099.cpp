#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
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
map<int,int>vis[N];
struct Link_Cut_Tree{
	struct Tree{
		int ch[2],fa,aux,rev,sum,data;
	}t[N];
	int Pushup(int x){
		t[x].sum=t[x].data^t[t[x].ch[0]].sum^t[t[x].ch[1]].sum;
	}
	int Pushdown(int x){
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
		else{
			t[x].aux=0;t[y].aux=1;
		}
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
				if(t[y].ch[0]==x^t[z].ch[0]==y)Rotate(x);
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
	int Find(int x){
		Access(x);Splay(x);
		while(t[x].ch[0])x=t[x].ch[0];
		return x;
	}
	void Evert(int x){Access(x);Splay(x);t[x].rev^=1;}
	void Split(int x,int y){Evert(x);Access(y);Splay(y);}
	void Link(int x,int y){Evert(x);t[x].fa=y;}
	void Cut(int x,int y){Split(x,y);t[x].aux=t[x].fa=t[y].ch[0]=0;Pushup(y);}
	void Change(int x,int y){Access(x);Splay(x);t[x].data=y;Pushup(x);}
	int Ask(int x,int y){Split(x,y);return t[y].sum;}
}Tree;
int n,m;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		Tree.Change(i,read());
	}
	while(m--){
		int op=read(),x=read(),y=read();
		if(op==0){
			printf("%d\n",Tree.Ask(x,y));
		}
		if(op==1){
			if(Tree.Find(x)==Tree.Find(y))continue;
			Tree.Link(x,y);vis[x][y]=1;
		}
		if(op==2){
			if(!vis[x][y])continue;
			Tree.Cut(x,y);vis[x][y]=0;
		}
		if(op==3){
			Tree.Change(x,y);
		}
	}
	return 0;
}