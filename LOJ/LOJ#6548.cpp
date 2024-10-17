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
#include<unordered_map>
#define ll long long
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
unordered_map<int,int>id[N];
int n,m,tot,qnt,pos[N],Ans[N];
struct Node{int x,y;}E[N],Q[N];
struct Tree{int ch[2],fa,aux,rev,val,Max;};
struct Link_Cut_Tree{
	Tree t[N];
	void Reverse(int p){t[p].rev^=1;swap(t[p].ch[0],t[p].ch[1]);}
	void Pushup(int p){
		t[p].Max=p;
		if(t[t[t[p].ch[0]].Max].val>t[t[p].Max].val)t[p].Max=t[t[p].ch[0]].Max;
		if(t[t[t[p].ch[1]].Max].val>t[t[p].Max].val)t[p].Max=t[t[p].ch[1]].Max;
	}
	void Pushdown(int p){if(t[p].rev){t[p].rev=0;Reverse(t[p].ch[0]);Reverse(t[p].ch[1]);}}
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
			t[x].ch[1]=y;
			t[t[x].ch[1]].aux=1;
			Pushup(x);y=x;x=t[x].fa;
		}
	}
	void Evert(int x){Access(x);Splay(x);Reverse(x);}
	void Split(int x,int y){Evert(x);Access(y);Splay(y);}
	void Link(int x,int y){Split(x,y);t[x].fa=y;}
	void Cut(int x,int y){Split(x,y);t[x].fa=t[x].aux=t[y].ch[0]=0;Pushup(y);}
	int Find(int x){Access(x);Splay(x);while(t[x].ch[0])x=t[x].ch[0];Splay(x);return x;}
	int Query1(int x,int y){if(Find(x)!=Find(y))return -1;Split(x,y);return t[y].Max;}
	int Query2(int x,int y){if(Find(x)!=Find(y))return -1;Split(x,y);return t[t[y].Max].val;}
}lct;
struct Segment_Tree{
	int top;
	Node st[N];//(Node){id,f}
	vector<int>F1[N*4],F2[N];
	void Link(int id){
		int op=lct.Query1(E[id].x,E[id].y);
		if(op==-1){
			st[++top]=(Node){id,1};lct.Link(id,E[id].x);lct.Link(id,E[id].y);
		}
		else if(lct.t[op].val>lct.t[id].val){
			st[++top]=(Node){op,-1};lct.Cut(op,E[op].x);lct.Cut(op,E[op].y);
			st[++top]=(Node){id,1};lct.Link(id,E[id].x);lct.Link(id,E[id].y);
		}
	}
	void Reset(int tmp){
		while(top>tmp){
			int id=st[top].x,f=st[top].y;top--;
			if(f==1){lct.Cut(id,E[id].x);lct.Cut(id,E[id].y);}
			if(f==-1){lct.Link(id,E[id].x);lct.Link(id,E[id].y);}
		}
	}
	void Update(int x,int y,int id,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){F1[p].push_back(id);return;}
		int mid=(l+r)>>1;
		Update(x,y,id,lson);Update(x,y,id,rson);
	}
	void Solve(int p,int l,int r){
		int tmp=top;
		for(auto id:F1[p])Link(id);
		if(l==r){for(auto id:F2[l])Ans[id]=lct.Query2(Q[id].x,Q[id].y);Reset(tmp);return;}
		int mid=(l+r)>>1;Solve(lson);Solve(rson);Reset(tmp);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();tot=n;
	for(int i=1;i<=m;i++){
		int op=read(),x=read()+1,y=read()+1;
		if(x>y)swap(x,y);
		if(op==0){E[++tot]=(Node){x,y};lct.t[tot].val=read();pos[tot]=i;id[x][y]=tot;}
		if(op==1){tree.Update(pos[id[x][y]],i-1,id[x][y],1,1,m);pos[id[x][y]]=0;id[x][y]=0;}
		if(op==2){Q[++qnt]=(Node){x,y};tree.F2[i].push_back(qnt);}
	}
	for(int i=n+1;i<=tot;i++)if(pos[i])tree.Update(pos[i],m,i,1,1,m);
	for(int i=1;i<=tot;i++)lct.t[i].Max=i;
	tree.Solve(1,1,m);
	for(int i=1;i<=qnt;i++)printf("%d\n",Ans[i]);
	return 0;
}
