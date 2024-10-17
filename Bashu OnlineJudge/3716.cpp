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
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,a[N],F1[N],F2[N];
int Find1(int x){return x==F1[x]?x:F1[x]=Find1(F1[x]);}
int Find2(int x){return x==F2[x]?x:F2[x]=Find2(F2[x]);}
struct Tree{int ch[2],fa,aux,rev,sum,val;};
struct Link_Cut_Tree{
	Tree t[N];
	void Pushup(int x){t[x].sum=t[x].val+t[t[x].ch[0]].sum+t[t[x].ch[1]].sum;}
	void Pushdown(int x){
		if(t[x].rev){
			t[x].rev=0;
			t[t[x].ch[0]].rev^=1;
			t[t[x].ch[1]].rev^=1;
			swap(t[x].ch[0],t[x].ch[1]);
		}
	}
	void Rotate(int x){
		int y=Find1(t[x].fa),z=Find1(t[y].fa);
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
			int y=Find1(t[x].fa),z=Find1(t[y].fa);
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
			Pushup(x);y=x;x=Find1(t[x].fa);
		}
	}
	void Evert(int x){Access(x);Splay(x);t[x].rev^=1;}
	void Split(int x,int y){Evert(x);Access(y);Splay(y);}
	void Link(int x,int y){Split(x,y);t[x].fa=y;}
	void Change(int x,int y){Evert(x);t[x].val+=y;Pushup(x);}
	int Query(int x,int y){Split(x,y);return t[y].sum;}
	void DFS(int x,int p){
		F1[x]=p;Pushdown(x);
		if(t[x].ch[0])DFS(Find1(t[x].ch[0]),p);
		if(t[x].ch[1])DFS(Find1(t[x].ch[1]),p);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		F1[i]=F2[i]=i;
		a[i]=tree.t[i].val=tree.t[i].sum=read();
	}
	while(m--){
		int op=read(),x=read(),y=read();
		if(op==1){
			x=Find1(x);y=Find1(y);
			if(x==y)continue;
			tree.Split(x,y);
			if(Find2(x)==Find2(y)){
				tree.t[y].val=tree.t[y].sum;
				tree.DFS(y,y);
				tree.t[y].ch[0]=tree.t[y].ch[1]=0;
			}
			else{
				tree.t[x].fa=y;
				F2[Find2(x)]=Find2(y);
			}
		}
		if(op==2){
			int dlt=y-a[x];a[x]=y;
			tree.Change(Find1(x),dlt);
		}
		if(op==3){
			if(Find2(x)!=Find2(y)){puts("-1");continue;}
			printf("%d\n",tree.Query(Find1(x),Find1(y)));
		}
	}
	return 0;
}