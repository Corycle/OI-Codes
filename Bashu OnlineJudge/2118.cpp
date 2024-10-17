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
const int S=500005;
const int N=100005;
const int M=26;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[S],t[N];
int n,m,pos[S],Len[S],Root[N];
struct Tree{int l,r,Max,pos;}Answer;
struct Segment_Tree{
	int tot;
	Tree t[N*150];
	Tree Max(Tree A,Tree B){
		if(B.Max>A.Max||(B.Max==A.Max&&B.pos<A.pos)){A.Max=B.Max;A.pos=B.pos;}
		return A;
	}
	void Pushup(int p){
		t[p].Max=t[p].pos=0;
		if(t[p].l)t[p]=Max(t[p],t[t[p].l]);
		if(t[p].r)t[p]=Max(t[p],t[t[p].r]);
	}
	void Insert(int x,int &p,int l,int r){
		if(!p)p=++tot;
		if(l==r){t[p].pos=l;t[p].Max++;return;}
		int mid=(l+r)>>1;
		if(x<=mid)Insert(x,t[p].l,l,mid);
		if(x>mid)Insert(x,t[p].r,mid+1,r);
		Pushup(p);
	}
	int Merge(int x,int y,int l,int r){
		if(!x||!y)return x|y;
		int p=++tot;
		if(l==r){t[p].pos=l;t[p].Max=t[x].Max+t[y].Max;return p;}
		int mid=(l+r)>>1;
		t[p].l=Merge(t[x].l,t[y].l,l,mid);
		t[p].r=Merge(t[x].r,t[y].r,mid+1,r);
		Pushup(p);
		return p;
	}
	void Query(int x,int y,int p,int l,int r){
		if(y<l||x>r||!p)return;
		if(x<=l&&r<=y){Answer=Max(Answer,t[p]);return;}
		int mid=(l+r)>>1;
		Query(x,y,t[p].l,l,mid);
		Query(x,y,t[p].r,mid+1,r);
	}
}tree;
struct SAM{
	vector<int>G[N];
	int tot=1,lst=1,root=1;
	int fa[N],len[N],ch[N][M],p[N][M];
	void Insert(int num,int id){
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
		tree.Insert(id,Root[fx],1,m);
	}
	int Climb(int x,int l){
		for(int k=(int)(log(tot)/log(2));k>=0;k--){
			if(len[p[x][k]]>=l)x=p[x][k];
		}
		return x;
	}
	void DFS(int x){
		for(auto y:G[x]){DFS(y);Root[x]=tree.Merge(Root[x],Root[y],1,m);}
	}
	void Build(){
		int k=(int)(log(tot)/log(2));
		for(int i=1;i<=tot;i++)p[i][0]=fa[i];
		for(int i=1;i<=tot;i++)G[fa[i]].push_back(i);
		for(int j=1;j<=k;j++){
			for(int i=1;i<=tot;i++){
				if(p[i][j-1])p[i][j]=p[p[i][j-1]][j-1];
			}
		}
		for(int i=1,p=1,d=0;i<=n;i++){
			int x=s[i]-'a';
			while(p&&!ch[p][x]){p=fa[p];d=len[p];}
			if(p){p=ch[p][x];d++;}
			else {p=root;d=0;}
			pos[i]=p;Len[i]=d;
		}
		DFS(root);
	}
}sam;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	scanf("%s",s+1);
	n=strlen(s+1);m=read();
	for(int i=1;i<=m;i++){
		sam.lst=1;
		scanf("%s",t+1);
		int len=strlen(t+1);
		for(int j=1;j<=len;j++){
			sam.Insert(t[j]-'a',i);
		}
	}
	sam.Build();
	int T=read();
	while(T--){
		int ql=read(),qr=read(),l=read(),r=read();
		if(Len[r]<r-l+1)printf("%d %d\n",ql,0);
		else{
			int p=sam.Climb(pos[r],r-l+1);
			Answer=(Tree){0,0,0,0};
			tree.Query(ql,qr,Root[p],1,m);
			if(!Answer.Max)Answer.pos=ql;
			printf("%d %d\n",Answer.pos,Answer.Max);
		}
	}
	return 0;
}