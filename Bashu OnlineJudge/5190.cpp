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
#define pii pair<int,int>
#define fst first
#define scd second
#define mp make_pair
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2e5+5;
const int M=26;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans[N];
char s[N];
vector<pii>G[N];
int n,m,ch[N][M],fa[N],len[N],pos[N];
struct BIT{
	ll c1[N],c2[N];
	int lowbit(int x){return x&(-x);}
	void Add(int x,ll y){ll z=x*y;for(int i=x;i<N;i+=lowbit(i))c1[i]+=y,c2[i]+=z;}
	ll Ask(int x){ll ans1=0,ans2=0;for(int i=x;i>=1;i-=lowbit(i))ans1+=c1[i],ans2+=c2[i];return ans1*(x+1)-ans2;}
	void Update(int l,int r,int x){Add(l,x);Add(r+1,-x);}
	ll Query(int l,int r){return Ask(r)-Ask(l-1);}
}tree;
struct Tree{int ch[2],fa,aux,tag,pos,val,data;};
struct Link_Cut_Tree{
	Tree t[N];
	void update(int x,int pos){t[x].tag=t[x].pos=pos;}
	void Pushup(int x){
		t[x].val=min(t[x].data,min(t[t[x].ch[0]].val,t[t[x].ch[1]].val));
	}
	void Pushdown(int x){
		if(t[x].tag){
			update(t[x].ch[0],t[x].tag);
			update(t[x].ch[1],t[x].tag);
			t[x].tag=0;
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
	void Access(int x,int pos){
		int y=0;
		while(x){
			Splay(x);
			t[t[x].ch[1]].aux=0;
			t[x].ch[1]=y;
			t[t[x].ch[1]].aux=1;
			Pushup(x);y=x;x=t[x].fa;
			if(t[y].pos)tree.Update(t[y].pos-len[y]+1,t[y].pos-t[y].val+1,-1);
		}
	}
	void Change(int x,int pos){
		Access(x,pos);Splay(x);update(x,pos);
		tree.Update(t[x].pos-len[x]+1,t[x].pos-t[x].val+1,1);
	}
}lct;
struct SAM{
	int tot=1,lst=1,root=1;
	void insert(int num){
		int x=lst,fx=++tot;len[fx]=len[x]+1;
		while(x&&!ch[x][num]){ch[x][num]=fx;x=fa[x];}
		if(!x)fa[fx]=root;
		else{
			int y=ch[x][num];
			if(len[y]==len[x]+1)fa[fx]=y;
			else{
				int fy=++tot;len[fy]=len[x]+1;
				fa[fy]=fa[y];fa[y]=fa[fx]=fy;
				memcpy(ch[fy],ch[y],sizeof(ch[fy]));
				while(x&&ch[x][num]==y){ch[x][num]=fy;x=fa[x];}
			}
		}
		lst=fx;
	}
}sam;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	scanf("%s",s+1);n=strlen(s+1);
	for(int i=1;i<=n;i++){sam.insert(s[i]-'a');pos[i]=sam.lst;}
	for(int i=1;i<=sam.tot;i++)lct.t[i].val=lct.t[i].data=len[lct.t[i].fa=fa[i]]+1;
	lct.t[0].val=inf;
	m=read();
	for(int i=1;i<=m;i++){
		int l=read(),r=read();
		G[r].push_back(mp(l,i));
	}
	for(int i=1;i<=n;i++){
		lct.Change(pos[i],i);
		for(auto Q:G[i]){
			Ans[Q.scd]=tree.Query(Q.fst,i);
		}
	}
	for(int i=1;i<=m;i++)printf("%lld\n",Ans[i]);
	return 0;
}