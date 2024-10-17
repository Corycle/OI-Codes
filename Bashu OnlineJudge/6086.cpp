/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<cstring>
#include<complex>
#include<vector>
#include<cstdio>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=5e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[10];
int n,m,Q,tot;
map<int,int>E[N];
struct Tree{int ch[2],fa,aux,rev;ll col,val,num,sum,lans,rans,inum,ians;};
struct Link_Cut_Tree{
	Tree t[N];
	void Reverse(int x){t[x].rev^=1;swap(t[x].ch[0],t[x].ch[1]);swap(t[x].lans,t[x].rans);}
	void Pushup(int x){
		t[x].sum=t[t[x].ch[0]].sum+t[t[x].ch[1]].sum+t[x].val;
		t[x].num=t[t[x].ch[0]].num+t[t[x].ch[1]].num+t[x].col+t[x].inum;
		t[x].lans=t[t[x].ch[0]].lans+t[t[x].ch[1]].lans+(t[x].col+t[t[x].ch[1]].num+t[x].inum)*(t[x].val+t[t[x].ch[0]].sum)+t[x].ians;
		t[x].rans=t[t[x].ch[0]].rans+t[t[x].ch[1]].rans+(t[x].col+t[t[x].ch[0]].num+t[x].inum)*(t[x].val+t[t[x].ch[1]].sum)+t[x].ians;
	}
	void Pushdown(int x){
		if(t[x].rev){
			t[x].rev=0;
			Reverse(t[x].ch[0]);
			Reverse(t[x].ch[1]);
		}
	}
	void Rotate(int x){
		int y=t[x].fa;int z=t[y].fa;
		int l=(x!=t[y].ch[0]),r=l^1;
		if(t[y].aux)t[z].ch[y!=t[z].ch[0]]=x;
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
			t[x].inum+=t[t[x].ch[1]].num;
			t[x].ians+=t[t[x].ch[1]].lans;
			t[x].ch[1]=y;
			t[t[x].ch[1]].aux=1;
			t[x].inum-=t[t[x].ch[1]].num;
			t[x].ians-=t[t[x].ch[1]].lans;
			Pushup(x);y=x;x=t[x].fa;
		}
	}
	void Evert(int x){Access(x);Splay(x);Reverse(x);}
	void Split(int x,int y){Evert(x);Access(y);Splay(y);}
	void Link(int x,int y){Evert(x);Evert(y);t[x].fa=y;t[y].inum+=t[x].num;t[y].ians+=t[x].lans;Pushup(y);}
	void Cut(int x,int y){Split(x,y);t[x].fa=t[x].aux=t[y].ch[0]=0;Pushup(y);}
	void ChangeColor(int x){Evert(x);t[x].col^=1;Pushup(x);}
	ll Query(int x){Evert(x);return t[x].lans;}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Q=read();tot=n;
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		tree.t[++tot].val=z;
		E[x][y]=E[y][x]=tot;
		tree.Pushup(tot);
		tree.Link(x,tot);
		tree.Link(y,tot);
	}
	while(Q--){
		scanf("%s",s);
		if(s[0]=='L'){
			int x=read(),y=read(),z=read();
			tree.t[++tot].val=z;
			E[x][y]=E[y][x]=tot;
			tree.Pushup(tot);
			tree.Link(x,tot);
			tree.Link(y,tot);
		}
		if(s[0]=='C'){
			int x=read(),y=read();
			tree.Cut(x,E[x][y]);
			tree.Cut(y,E[x][y]);
			E[x][y]=E[y][x]=0;
		}
		if(s[0]=='F')tree.ChangeColor(read());
		if(s[0]=='Q')printf("%lld\n",tree.Query(read()));
	}
	return 0;
}