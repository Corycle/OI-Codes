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
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
vector<int>G[N];
struct Heap{
	priority_queue<int>q1,q2;
	void Insert(int x){q1.push(x);}
	void Delete(int x){q2.push(x);}
	int Top(){
		while(!q1.empty()&&!q2.empty()&&q1.top()==q2.top()){q1.pop();q2.pop();}
		return q1.empty()?-inf:q1.top();
	}
}Max[N][2];
struct Tree{int ch[2],fa,aux,val,lc,rc,col,tag,lmax,rmax;};
struct Link_Cut_Tree{
	Tree t[N];
	void Pushup(int x){
		int l=t[x].ch[0],r=t[x].ch[1];
		t[x].lc=(l?t[l].lc:t[x].col);
		t[x].rc=(r?t[r].rc:t[x].col);
		t[x].tag=((t[l].tag==2||t[r].tag==2||(l&&t[l].col!=t[x].col)||(r&&t[r].col!=t[x].col))?2:t[x].col);
		t[x].lmax=max(t[l].lmax,(!l||(t[l].tag!=2&&t[l].lc==t[x].col))?max(t[x].val,max(Max[x][t[x].col].Top(),(t[r].lc==t[x].col?t[r].lmax:-inf))):-inf);
		t[x].rmax=max(t[r].rmax,(!r||(t[r].tag!=2&&t[r].rc==t[x].col))?max(t[x].val,max(Max[x][t[x].col].Top(),(t[l].rc==t[x].col?t[l].rmax:-inf))):-inf);
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
			if(t[x].ch[1])Max[x][t[t[x].ch[1]].lc].Insert(t[t[x].ch[1]].lmax);
			t[t[x].ch[1]].aux=0;t[x].ch[1]=y;t[t[x].ch[1]].aux=1;
			if(t[x].ch[1])Max[x][t[t[x].ch[1]].lc].Delete(t[t[x].ch[1]].lmax);
			Pushup(x);y=x;x=t[x].fa;
		}
	}
	void ChangeColor(int x){Access(x);Splay(x);t[x].col^=1;Pushup(x);}
	void Change(int x,int y){Access(x);Splay(x);t[x].val=y;Pushup(x);}
	int Query(int x){Access(x);Splay(x);return t[x].rmax;}
}tree;
void DFS(int x,int fa){
	tree.Pushup(x);
	for(auto y:G[x]){
		if(y==fa)continue;
		DFS(y,x);
		tree.t[y].fa=x;
		Max[x][tree.t[y].lc].Insert(tree.t[y].lmax);
		tree.Pushup(x);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		G[x].push_back(y);
		G[y].push_back(x);
	}
	tree.t[0].lmax=tree.t[0].rmax=-inf;
	for(int i=1;i<=n;i++)tree.t[i].col=read();
	for(int i=1;i<=n;i++)tree.t[i].val=read();
	DFS(1,0);
	m=read();
	while(m--){
		int op=read(),x=read();
		if(op==0)printf("%d\n",tree.Query(x));
		if(op==1)tree.ChangeColor(x);
		if(op==2)tree.Change(x,read());
	}
	return 0;
}