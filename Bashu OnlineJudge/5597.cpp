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
const int N=200005;
const int M=3;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Sum;
char s[N],c[M];
int n,m,cnt,h[N],vis[N],pos[N];
struct edge{int to,next;char v;}d[N];
void Add(int x,int y,char z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
/*========LCT========*/
struct Tree{int ch[2],fa,aux,rev,val,tag;};
struct Link_Cut_Tree{
	Tree t[N];
	void update(int x,int y){
		if(x){t[x].val+=y;t[x].tag+=y;}
	}
	void Pushdown(int x){
		if(t[x].rev){
			t[x].rev=0;
			t[t[x].ch[0]].rev^=1;
			t[t[x].ch[1]].rev^=1;
			swap(t[x].ch[0],t[x].ch[1]);
		}
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
		t[x].fa=z;t[y].fa=x;t[t[x].ch[r]].fa=y;
		t[y].ch[l]=t[x].ch[r];t[x].ch[r]=y;
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
			t[t[x].ch[1]].aux=0;t[x].ch[1]=y;
			t[t[x].ch[1]].aux=1;y=x;x=t[x].fa;
		}
	}
	void Evert(int x){Access(x);Splay(x);t[x].rev^=1;}
	void Split(int x,int y){Evert(x);Access(y);Splay(y);}
	void Link(int x,int y){Split(x,y);t[x].fa=y;}
	void Cut(int x,int y){Split(x,y);t[x].fa=t[x].aux=t[y].ch[0]=0;}
	void Add(int x,int y,int addv){Split(x,y);update(y,addv);}
}tree;
/*========SAM========*/
struct SAM{
	int tot=1,lst=1,root=1;
	int ch[N][M],fa[N],len[N];
	void Insert(int num){
		int x=lst,fx=++tot;len[fx]=len[x]+1;
		while(x&&!ch[x][num]){ch[x][num]=fx;x=fa[x];}
		if(!x){fa[fx]=root;tree.Link(fx,fa[fx]);}
		else{
			int y=ch[x][num];
			if(len[y]==len[x]+1){fa[fx]=y;tree.Link(fx,fa[fx]);}
			else{
				int fy=++tot;len[fy]=len[x]+1;
				tree.Evert(y);
				tree.t[fy].val=tree.t[y].val;
				tree.Cut(y,fa[y]);
				fa[fy]=fa[y];fa[y]=fa[fx]=fy;
				tree.Link(y,fa[y]);
				tree.Link(fy,fa[fy]);
				tree.Link(fx,fa[fx]);
				memcpy(ch[fy],ch[y],sizeof(ch[fy]));
				while(x&&ch[x][num]==y){ch[x][num]=fy;x=fa[x];}
			}
		}
		lst=fx;
		tree.Add(root,fx,1);
		Sum+=len[fx]-len[fa[fx]];
	}
	void Query(){
		scanf("%s",s+1);
		int Ans=0,p=root,len=strlen(s+1);
		for(int i=1;i<=len;i++)p=ch[p][(int)(s[i]-'a')];
		if(p){tree.Evert(p);Ans=tree.t[p].val;}
		printf("%d\n",Ans);
	}
}sam;
/*========Operation========*/
void DFS(int x){
	vis[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(vis[y])continue;
		sam.lst=pos[x];
		sam.Insert(d[i].v-'a');
		pos[y]=sam.lst;
		DFS(y);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	read();n=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		scanf("%s",c);
		Add(x,y,c[0]);
		Add(y,x,c[0]);
	}
	pos[1]=1;DFS(1);
	m=read();
	while(m--){
		int op=read();
		if(op==1)printf("%lld\n",Sum);
		if(op==2){
			int sx=read(),Size=read();
			for(int i=1;i<Size;i++){
				int x=read(),y=read();
				scanf("%s",c);
				Add(x,y,c[0]);
				Add(y,x,c[0]);
			}
			n+=Size-1;
			DFS(sx);
		}
		if(op==3)sam.Query();
	}
	return 0;
}