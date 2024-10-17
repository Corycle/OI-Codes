/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,tot=1,lst=1,root=1;
int fa[N],len[N],ch[N][2],vis[N],Ans[N];
struct Ques{int l,r,id;}Q[N];
bool cmp(Ques A,Ques B){
	if(A.r==B.r)return A.l<B.l;
	return A.r<B.r;
}
void SAM(int num){
	int x=lst,fx=++tot;len[fx]=len[x]+1;
	while(x&&!ch[x][num]){ch[x][num]=fx;x=fa[x];}
	if(!x)fa[fx]=root;
	else{
		int y=ch[x][num];
		if(len[y]==len[x]+1)fa[fx]=y;
		else{
			int fy=++tot;len[fy]=len[x]+1;
			for(int i=0;i<2;i++)ch[fy][i]=ch[y][i];
			fa[fy]=fa[y];fa[y]=fa[fx]=fy;vis[fy]=vis[y];
			while(x&&ch[x][num]==y){ch[x][num]=fy;x=fa[x];}
		}
	}
	lst=fx;
}
struct Segment_Tree{
	struct Tree{int Max;}t[N*4];
	void Pushup(int p){
		t[p].Max=max(t[p<<1].Max,t[p<<1|1].Max);
	}
	void Add(int x,int y,int p,int l,int r){
		if(x<l||x>r)return;
		if(l==r){
			t[p].Max=max(t[p].Max,y);
			return;
		}
		int mid=(l+r)>>1;
		Add(x,y,lson);Add(x,y,rson);
		Pushup(p);
	}
	int Ask(int x,int y,int p,int l,int r){
		if(y<l||x>r)return -inf;
		if(x<=l&&r<=y)return t[p].Max;
		int mid=(l+r)>>1;
		return max(Ask(x,y,lson),Ask(x,y,rson));
	}
}tree;
void Solve(int x,int id){
	while(x){
		if(vis[x]&&len[x]){
			tree.Add(vis[x],len[x],1,1,n);
		}
		vis[x]=id;x=fa[x];
	}
}
int main(){
//	freopen("A.in","r",stdin);
//	freopen("A.out","w",stdout);
	n=read();m=read();
	scanf("%s",s+1);
	for(int i=1;i<=m;i++){
		Q[i].id=i;
		Q[i].l=read();
		Q[i].r=read();
	}
	int l=1;
	sort(Q+1,Q+m+1,cmp);
	for(int i=1;i<=n;i++){
		SAM(s[i]-'0');
		Solve(lst,i);
		if(Q[l].r==i){
			int r=l;
			while(Q[r+1].r==i)r++;
			for(int j=l;j<=r;j++){
				Ans[Q[j].id]=tree.Ask(Q[j].l,Q[j].r,1,1,n);
			}
			l=r+1;
		}
	}
	for(int i=1;i<=m;i++)printf("%d\n",Ans[i]);
	return 0;
}