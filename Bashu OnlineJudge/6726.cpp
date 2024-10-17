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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
struct Splay_Tree{
	int tot,root;
	struct Tree{int ch[2],fa,rev,sum,pos,id;}t[N];
	void Pushup(int x){
		t[x].sum=t[t[x].ch[0]].sum+t[t[x].ch[1]].sum+1;
	}
	void Pushdown(int x){
		if(t[x].rev){
			t[x].rev=0;
			t[t[x].ch[0]].rev^=1;
			t[t[x].ch[1]].rev^=1;
			swap(t[x].ch[0],t[x].ch[1]);
		}
	}
	void Rotate(int x,int &f){
		int y=t[x].fa;int z=t[y].fa;
		int l=(x!=t[y].ch[0]),r=l^1;
		if(y!=f){
			if(y==t[z].ch[0])t[z].ch[0]=x;
			else t[z].ch[1]=x;
		}
		else f=x;
		t[x].fa=z;t[y].fa=x;
		t[t[x].ch[r]].fa=y;
		t[y].ch[l]=t[x].ch[r];
		t[x].ch[r]=y;
		Pushup(y);Pushup(x);
	}
	void Splay(int x,int &f){
		Pushdown(x);
		while(x!=f){
			int y=t[x].fa,z=t[y].fa;
			if(y!=f)Pushdown(z);
			Pushdown(y);Pushdown(x);
			if(y!=f){
				if((x==t[y].ch[0])^(y==t[z].ch[0]))Rotate(x,f);
				else Rotate(y,f);
			}
			Rotate(x,f);
		}
	}
	void Insert(int pos,int x){
		int p=root,f=0;
		while(p){
			f=p;t[p].sum++;
			if(pos<=t[p].pos)p=t[p].ch[0];
			else p=t[p].ch[1];
		}
		tot++;
		t[tot].id=x;t[tot].pos=pos;
		t[tot].fa=f;t[tot].sum=1;
		if(!root){root=tot;return;}
		if(pos<=t[f].pos)t[f].ch[0]=tot;
		else t[f].ch[1]=tot;
		Splay(tot,root);
	}
	int Find(int k){
		int p=root;
		while(1){
			Pushdown(p);
			if(k==t[t[p].ch[0]].sum+1){Splay(p,root);return p;}
			if(k<=t[t[p].ch[0]].sum)p=t[p].ch[0];
			else{k=k-t[t[p].ch[0]].sum-1;p=t[p].ch[1];}
		}
	}
	void Reverse(int l,int r){
		int x=Find(l),y=Find(r+2);
		Splay(x,root);
		Splay(y,t[x].ch[1]);
		t[t[y].ch[0]].rev^=1;
	}
	void Print(int x){
		Pushdown(x);
		if(t[x].ch[0])Print(t[x].ch[0]);
		if(t[x].id)printf("%d ",t[x].id);
		if(t[x].ch[1])Print(t[x].ch[1]);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	tree.Insert(0,0);tree.Insert(n+1,0);
	for(int i=1;i<=n;i++)tree.Insert(i,i);
	while(m--){int l=read(),r=read();tree.Reverse(l,r);}
	tree.Print(tree.root);
	return 0;
}