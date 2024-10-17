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
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=200005;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
int n,m,cnt,tot;
int h[N],B[N],L[N],id[N],pos[N],sum[N];
struct edge{int to,next;}d[N];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
int dlt[8];
bool cmp(int x,int y){return x>y;}
struct Tree{int b1,b2,b3,l1,l2;}Ans;
Tree Merge(Tree &A,Tree &B){
	Tree P=(Tree){-1,-1,-1,-1,-1};
	//Get b1,b2,b3
	dlt[1]=A.b1;dlt[2]=A.b2;dlt[3]=A.b3;
	dlt[4]=B.b1;dlt[5]=B.b2;dlt[6]=B.b3;
	sort(dlt+1,dlt+6+1,cmp);
	P.b1=dlt[1];P.b2=dlt[2];
	for(int i=6;i>=3;i--)if(dlt[i]<dlt[2])P.b3=dlt[i];
	//Get l1,l2
	dlt[1]=A.l1;dlt[2]=A.l2;
	dlt[3]=B.l1;dlt[4]=B.l2;
	sort(dlt+1,dlt+4+1,cmp);
	P.l1=dlt[1];
	for(int i=4;i>=2;i--)if(dlt[i]<dlt[1])P.l2=dlt[i];
	//Finish
	return P;
}
struct Segment_Tree{
	Tree t[N*4];
	void Build(int p,int l,int r){
		if(l==r){
			t[p].b1=B[pos[l]];
			t[p].l1=L[pos[l]];
			return;
		}
		int mid=(l+r)>>1;
		Build(lson);Build(rson);
		t[p]=Merge(t[p<<1],t[p<<1|1]);
	}
	void Ask(int x,int y,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){Ans=Merge(Ans,t[p]);return;}
		int mid=(l+r)>>1;Ask(x,y,lson);Ask(x,y,rson);
	}
}tree;
// Tree x: id[x]~id[x]+sum[x]-1 
void DFS(int x){
	sum[x]=1;pos[id[x]=++tot]=x;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;DFS(y);
		sum[x]=sum[x]+sum[y];
	}
}
int main(){
//	freopen("soldier.in","r",stdin);
//	freopen("soldier.out","w",stdout);
	n=read();m=read();
	for(int i=2;i<=n;i++)Add(read(),i);
	for(int i=1;i<=n;i++){
		B[i]=read();
		L[i]=read();
	}
	DFS(1);
	tree.Build(1,1,n);
	while(m--){
		int x=read();
		int l=id[x],r=id[x]+sum[x]-1;
		Ans=(Tree){-1,-1,-1,-1,-1};
		tree.Ask(l,r,1,1,n);
		int b1=Ans.b1,b2=Ans.b2,b3=Ans.b3;
		Ans=(Tree){-1,-1,-1,-1,-1};
		if(1<l)tree.Ask(1,l-1,1,1,n);
		if(r<n)tree.Ask(r+1,n,1,1,n);
		int l1=Ans.l1,l2=Ans.l2;
		if(sum[x]==1)printf("0\n");//b2=-1
		else if(x==1){//l1=-1
			int ans=0;
			if(b1!=b2)ans=max(ans,b2);
			if(b3!=-1)ans=max(ans,b3);
			printf("%d\n",ans);
		}
		else{
			if(b2+l1>b1)printf("%d\n",b1);
			else if(b2+l1<b1)printf("%d\n",b2+l1);
			else if(b2+l1==b1){
				int ans=0;
				if(l2!=-1)ans=max(ans,b2+l2);
				if(b3!=-1)ans=max(ans,b3+l1);
				printf("%d\n",ans);
			}
		}
	}
	return 0;
}