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
const int N=500005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
int n,m,tot,Root;
struct BIT{
	int c[N*2];
	int lowbit(int x){return x&(-x);}
	void Add(int x,int y){for(;x<=n+m;x+=lowbit(x))c[x]+=y;}
	int Ask(int x){int ans=0;for(;x>=1;x-=lowbit(x))ans+=c[x];return ans;}
}tree;
struct Tree{int ch[2],fa,aux,rev,col,tot,L,R;};
struct Link_Cut_Tree{
	Tree t[N];
	void Pushup(int x){
		t[x].L=(t[x].ch[0]?t[t[x].ch[0]].L:x);
		t[x].R=(t[x].ch[1]?t[t[x].ch[1]].R:x);
		t[x].tot=t[t[x].ch[0]].tot+t[t[x].ch[1]].tot+1;
	}
	void Pushdown(int x){
		t[t[x].ch[0]].col=t[x].col;
		t[t[x].ch[1]].col=t[x].col;
		if(t[x].rev){
			t[x].rev=0;
			t[t[x].ch[0]].rev^=1;
			t[t[x].ch[1]].rev^=1;
			swap(t[x].L,t[x].R);
			swap(t[x].ch[0],t[x].ch[1]);
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
	void Access(int x,int c){
		int y=0;
		while(x){
			Splay(x);
			int sum=t[x].tot-t[t[x].ch[1]].tot;
			tree.Add(t[x].col,-sum);
			tree.Add(c,sum);
			t[x].col=c;
			t[t[x].ch[1]].aux=0;
			t[x].ch[1]=y;
			t[t[x].ch[1]].aux=1;
			Pushup(x);y=x;x=t[x].fa;
		}
	}
	void Evert(int x,int c){Access(x,c);Splay(x);t[x].rev^=1;}
}lct;
void DFS(int x,int fa){
	for(auto y:G[x]){
		if(y==fa)continue;
		lct.t[y].fa=x;
		DFS(y,x);
	}
}
char op[5];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		lct.t[i].L=i;
		lct.t[i].R=i;
		lct.t[i].tot=1;
		lct.t[i].col=i;
		tree.Add(i,1);
	}
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		G[x].push_back(y);
		G[y].push_back(x);
	}
	DFS(n,0);Root=n;tot=n;
	for(int i=1;i<=n;i++)lct.Access(i,i);
	for(int i=1;i<=m;i++){
		scanf("%s",op);
		int x=read();
		if(op[0]=='Q'){
			lct.Splay(x);
			int c=lct.t[x].col;
			int Ans=tree.Ask(c-1)+lct.t[lct.t[x].ch[1]].tot+1;
			printf("%d\n",Ans);
		}
		if(op[0]=='M'){
			tot++;
			int d=lct.t[Root].R;
			int c=lct.t[Root].col;
			lct.Evert(x,c);
			lct.Access(d,c);
			lct.Access(x,tot);
			Root=x;
		}
	}
	return 0;
}