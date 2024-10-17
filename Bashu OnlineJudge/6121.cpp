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
struct Tree{int ch[2],fa,aux,val,sum,lmax,rmax;};
struct Heap{
	priority_queue<int>q1,q2;
	void Insert(int x){q1.push(x);}
	void Delete(int x){q2.push(x);}
	int Top(){
		while(q1.size()&&q2.size()&&q1.top()==q2.top()){q1.pop();q2.pop();}
		return (q1.empty()?-inf:q1.top());
	}
}F[N];
struct Link_Cut_Tree{
	Tree t[N];
	void Pushup(int x){
		int l=t[x].ch[0],r=t[x].ch[1];
		t[x].sum=t[x].val+t[l].sum+t[r].sum;
		t[x].lmax=max(t[l].lmax,t[l].sum+t[x].val+max(0,max(t[r].lmax,F[x].Top())));
		t[x].rmax=max(t[r].rmax,t[r].sum+t[x].val+max(0,max(t[l].rmax,F[x].Top())));
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
		while(t[x].aux){
			int y=t[x].fa,z=t[y].fa;
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
			if(t[x].ch[1])F[x].Insert(t[t[x].ch[1]].lmax);
			t[t[x].ch[1]].aux=0;
			t[x].ch[1]=y;
			t[t[x].ch[1]].aux=1;
			if(t[x].ch[1])F[x].Delete(t[t[x].ch[1]].lmax);
			Pushup(x);y=x;x=t[x].fa;
		}
	}
	int Query(int x){Access(x);Splay(x);return t[x].rmax;}
	void Change(int x,int y){Access(x);Splay(x);t[x].val=y;Pushup(x);}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	tree.t[0].lmax=tree.t[0].rmax=-inf;
	for(int i=2;i<=n;i++)tree.t[i].fa=read();
	for(int i=1;i<=n;i++)tree.t[i].val=(read());
	for(int i=n;i>=1;i--){
		tree.Pushup(i);
		F[tree.t[i].fa].Insert(tree.t[i].lmax);
	}
	while(m--){
		int op=read(),x=read();
		if(op==1)printf("%d\n",tree.Query(x));
		if(op==2)tree.Change(x,read());
	}
	return 0;
}