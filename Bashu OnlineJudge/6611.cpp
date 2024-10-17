/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<cstring>
#include<complex>
#include<vector>
#include<cstdio>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<stack>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=525015;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
int n,m,cnt;
int a[N],h[N],fa[N],Root[N];
struct edge{int to,next;}d[N];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
struct Tree{int sum,ans,dep,ch[2];};
struct Trie{
	int tot;
	Tree t[N*26];
	int NewNode(int d){t[++tot].dep=d;return tot;}
	void Pushup(int x){
		t[x].sum=t[x].ans=0;
		if(t[x].ch[0]){
			t[x].sum+=t[t[x].ch[0]].sum;
			t[x].ans^=t[t[x].ch[0]].ans;
		}
		if(t[x].ch[1]){
			t[x].sum+=t[t[x].ch[1]].sum;
			t[x].ans^=t[t[x].ch[1]].ans;
			if(t[t[x].ch[1]].sum&1){
				t[x].ans^=(1<<t[x].dep);
			}
		}
	}
	int Merge(int x,int y){
		if(!x||!y)return x|y;
		t[x].sum+=t[y].sum;
		t[x].ans^=t[y].ans;
		t[x].ch[0]=Merge(t[x].ch[0],t[y].ch[0]);
		t[x].ch[1]=Merge(t[x].ch[1],t[y].ch[1]);
		return x;
	}
	void Update(int x){
		if(t[x].ch[1])Update(t[x].ch[1]);
		swap(t[x].ch[0],t[x].ch[1]);
		Pushup(x);
	}
	void Insert(int p,int d,int val){
		if(d==25){t[p].sum++;return;}
		int c=(val>>d)&1;
		if(!t[p].ch[c])t[p].ch[c]=NewNode(d+1);
		Insert(t[p].ch[c],d+1,val);
		Pushup(p);
	}
}tree;
void DFS(int x){
	Root[x]=tree.NewNode(0);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;DFS(y);
		Root[x]=tree.Merge(Root[x],Root[y]);
	}
	tree.Update(Root[x]);
	tree.Insert(Root[x],0,a[x]);
	Ans+=tree.t[Root[x]].ans;
}
int main(){
//	freopen("tree.in","r",stdin);
//	freopen("tree.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=2;i<=n;i++)Add(fa[i]=read(),i);
	DFS(1);
	printf("%lld",Ans);
	return 0;
}