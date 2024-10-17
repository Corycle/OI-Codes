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
#define lson t[p].l,l,mid
#define rson t[p].r,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=400005;
const int M=26;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,Ans,F[N],Root[N];
struct Tree{int l,r,sum;};
struct Segment_Tree{
	int tot;
	Tree t[N*M];
	void Insert(int x,int &p,int l,int r){
		if(!p)p=++tot;t[p].sum++;
		if(l==r)return;int mid=(l+r)>>1;
		if(x<=mid)Insert(x,lson);
		if(x>mid) Insert(x,rson);
	}
	int Ask(int x,int y,int p,int l,int r){
		if(y<l||x>r||!p)return 0;
		if(x<=l&&r<=y)return t[p].sum;
		int mid=(l+r)>>1;
		return Ask(x,y,lson)+Ask(x,y,rson);
	}
	int Merge(int x,int y){
		if(!x||!y)return x|y;
		int p=++tot;
		t[p].l=Merge(t[x].l,t[y].l);
		t[p].r=Merge(t[x].r,t[y].r);
		t[p].sum=t[t[p].l].sum+t[t[p].r].sum;
		return p;
	}
}tree;
struct SAM{
	vector<int>G[N];
	int tot,lst,root;
	int a[N],fa[N],len[N],ch[N][M];
	void Insert(int num){
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
		lst=fx;a[fx]=len[fx];
	}
	void Build(){
		tot=1;lst=1;root=1;
		for(int i=1;i<=n;i++)Insert(s[i]-'a');
		for(int i=1;i<=tot;i++)G[fa[i]].push_back(i);
	}
	void DFS(int x){
		if(a[x])tree.Insert(a[x],Root[x],1,n);
		for(auto y:G[x]){
			DFS(y);
			a[x]=max(a[x],a[y]);//Right
			Root[x]=tree.Merge(Root[x],Root[y]);
		}
	}
	void Solve(int x,int pre){
		if(x==root){F[x]=0;pre=x;}
		else if(fa[x]==root){F[x]=1;pre=x;}
		else{
			int tmp=tree.Ask((a[x]-len[x])+len[pre],a[x]-1,Root[pre],1,n);
			if(tmp){F[x]=F[pre]+1;pre=x;}
			else F[x]=F[pre];
		}
		for(auto y:G[x])Solve(y,pre);
		Ans=max(Ans,F[x]);
	}
}sam;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();scanf("%s",s+1);
	sam.Build();sam.DFS(1);sam.Solve(1,0);
	printf("%d",Ans);
	return 0;
}
