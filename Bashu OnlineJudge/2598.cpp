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
struct Tree{int ch[2],fa,aux,lc,rc,col,tag,lans,rans,sum[2];};
struct Link_Cut_Tree{
	Tree t[N];
	void Pushup(int x){
		int l=t[x].ch[0],r=t[x].ch[1];
		t[x].lc=(l?t[l].lc:t[x].col);
		t[x].rc=(r?t[r].rc:t[x].col);
		t[x].tag=((t[l].tag==2||t[r].tag==2||(l&&t[l].col!=t[x].col)||(r&&t[r].col!=t[x].col))?2:t[x].col);
		t[x].lans=t[l].lans+((!l||(t[l].tag!=2&&t[l].lc==t[x].col))?t[x].sum[t[x].col]+1+(t[r].lc==t[x].col?t[r].lans:0):0);
		t[x].rans=t[r].rans+((!r||(t[r].tag!=2&&t[r].rc==t[x].col))?t[x].sum[t[x].col]+1+(t[l].rc==t[x].col?t[l].rans:0):0);
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
			t[x].sum[t[t[x].ch[1]].lc]+=t[t[x].ch[1]].lans;
			t[t[x].ch[1]].aux=0;t[x].ch[1]=y;t[t[x].ch[1]].aux=1;
			t[x].sum[t[t[x].ch[1]].lc]-=t[t[x].ch[1]].lans;
			Pushup(x);y=x;x=t[x].fa;
		}
	}
	void Change(int x){Access(x);Splay(x);t[x].col^=1;Pushup(x);}
	int Query(int x){Access(x);Splay(x);return t[x].rans;}
}tree;
void DFS(int x,int fa){
	tree.Pushup(x);
	for(auto y:G[x]){
		if(y==fa)continue;
		DFS(y,x);
		tree.t[y].fa=x;
		tree.t[x].sum[tree.t[y].lc]+=tree.t[y].lans;
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
	DFS(1,0);
	m=read();
	while(m--){
		int op=read(),x=read();
		if(op==0)printf("%d\n",tree.Query(x));
		if(op==1)tree.Change(x);
	}
	return 0;
}