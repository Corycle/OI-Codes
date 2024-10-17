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
const int N=200005;
const int M=26;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,Root[N];
struct Tree{int l,r,tag;};
struct Segment_Tree{
	int tot;
	Tree t[N*20];
	void Insert(int &p,int x,int l,int r){
		if(!p)p=++tot;t[p].tag=1;
		if(l==r)return;int mid=(l+r)>>1;
		if(x<=mid)Insert(t[p].l,x,l,mid);
		if(x>mid)Insert(t[p].r,x,mid+1,r);
	}
	int Merge(int x,int y){
		if(!x||!y)return x|y;
		int p=++tot;
		t[p].tag=t[x].tag|t[y].tag;
		t[p].l=Merge(t[x].l,t[y].l);
		t[p].r=Merge(t[x].r,t[y].r);
		return p;
	}
	int Query(int x,int y,int p,int l,int r){
		if(y<l||x>r||!p)return 0;
		if(x<=l&&r<=y)return t[p].tag;
		int mid=(l+r)>>1;
		return Query(x,y,lson)|Query(x,y,rson);
	}
}tree;
struct SAM{
	vector<int>G[N];
	int tot=1,lst=1,root=1;
	int ch[N][M],fa[N],len[N],pos[N],p[N][20];
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
		lst=fx;pos[len[fx]]=fx;
	}
	void ST(){
		int k=(int)(log(tot)/log(2));
		for(int i=1;i<=tot;i++)p[i][0]=fa[i];
		for(int j=1;j<=k;j++){
			for(int i=1;i<=tot;i++){
				if(p[i][j-1])p[i][j]=p[p[i][j-1]][j-1];
			}
		}
	}
	int Climb(int x,int Len){
		for(int k=(int)(log(len[x])/log(2));k>=0;k--){
			if(len[p[x][k]]>=Len)x=p[x][k];
		}
		return x;
	}
	void DFS(int x){
		for(auto y:G[x]){DFS(y);Root[x]=tree.Merge(Root[x],Root[y]);}
	}
	void Build(){
		for(int i=1;i<=n;i++)tree.Insert(Root[pos[i]],i,1,n);
		for(int i=1;i<=tot;i++)G[fa[i]].push_back(i);
		DFS(root);ST();
	}
}sam;
bool Check(int a,int b,int c,int d,int mid){
	int p=sam.Climb(sam.pos[c+mid-1],mid);
	return tree.Query(a+mid-1,b,Root[p],1,n);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();scanf("%s",s+1);
	for(int i=1;i<=n;i++)sam.Insert(s[i]-'a');
	sam.Build();
	while(m--){
		int a=read(),b=read(),c=read(),d=read();
		int l=1,r=min(b-a+1,d-c+1),Ans=0;
		while(l<=r){
			int mid=(l+r)>>1;
			if(Check(a,b,c,d,mid)){
				Ans=mid;l=mid+1;
			}
			else r=mid-1;
		}
		printf("%d\n",Ans);
	}
	return 0;
}