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
char op[5];
int n,m,tot,fa[N],root[N];
int Find(int x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
struct Tree{int l,r,tag,Max;};
struct Heap{
	priority_queue<int>q1,q2;
	void Insert(int x){q1.push(x);}
	void Delete(int x){q2.push(x);}
	int Top(){
		while(q2.size()&&q1.top()==q2.top()){q1.pop();q2.pop();}
		return q1.top();
	}
}F;
struct Segment_Tree{
	Tree t[N*20];
	void update(int x,int addv){
		t[x].tag+=addv;
		t[x].Max+=addv;
	}
	void Pushdown(int x){
		if(t[x].tag){
			if(t[x].l)update(t[x].l,t[x].tag);
			if(t[x].r)update(t[x].r,t[x].tag);
			t[x].tag=0;
		}
	}
	void Update(int x,int y,int &p,int l,int r){
		if(!p){p=++tot;t[p].Max=-inf;}
		if(l==r){
			if(t[p].Max==-inf)t[p].Max=0;
			t[p].Max+=y;
			return;
		}
		int mid=(l+r)>>1;Pushdown(p);
		if(x<=mid)Update(x,y,t[p].l,l,mid);
		else Update(x,y,t[p].r,mid+1,r);
		t[p].Max=max(t[t[p].l].Max,t[t[p].r].Max);
	}
	int Merge(int x,int y,int l,int r){
		if(!x||!y)return x|y;
		int mid=(l+r)>>1;
		Pushdown(x);Pushdown(y);
		t[x].Max=max(t[x].Max,t[y].Max);
		t[x].l=Merge(t[x].l,t[y].l,l,mid);
		t[x].r=Merge(t[x].r,t[y].r,mid+1,r);
		return x;
	}
	int Ask(int x,int p,int l,int r){
		if(l==r)return t[p].Max;
		int mid=(l+r)>>1;Pushdown(p);
		if(x<=mid)return Ask(x,t[p].l,l,mid);
		else return Ask(x,t[p].r,mid+1,r);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	int tmp=0;tree.t[0].Max=-inf;
	for(int i=1;i<=n;i++){
		fa[i]=i;
		int x=read();F.Insert(x);
		tree.Update(i,x,root[i],1,n);
	}
	m=read();
	while(m--){
		scanf("%s",op);
		if(op[0]=='U'){
			int x=Find(read()),y=Find(read());
			if(x!=y){
				fa[y]=x;
				F.Delete(tree.t[root[x]].Max);
				F.Delete(tree.t[root[y]].Max);
				root[x]=tree.Merge(root[x],root[y],1,n);
				F.Insert(tree.t[root[x]].Max);
			}
		}
		if(op[0]=='A'&&op[1]=='1'){
			int x=read(),y=read();
			F.Delete(tree.t[root[Find(x)]].Max);
			tree.Update(x,y,root[Find(x)],1,n);
			F.Insert(tree.t[root[Find(x)]].Max);
		}
		if(op[0]=='A'&&op[1]=='2'){
			int x=Find(read()),y=read();
			F.Delete(tree.t[root[x]].Max);
			tree.update(root[x],y);
			F.Insert(tree.t[root[x]].Max);
		}
		if(op[0]=='A'&&op[1]=='3')tmp+=read();
		if(op[0]=='F'&&op[1]=='1'){int x=read();printf("%d\n",tree.Ask(x,root[Find(x)],1,n)+tmp);}
		if(op[0]=='F'&&op[1]=='2'){int x=root[Find(read())];printf("%d\n",tree.t[x].Max+tmp);}
		if(op[0]=='F'&&op[1]=='3')printf("%d\n",F.Top()+tmp);
	}
	return 0;
}