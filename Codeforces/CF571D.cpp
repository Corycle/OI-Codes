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
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans[N];
char s[10];
vector<int>G1[N],G2[N];
int L1[N],R1[N],f1[N],sum1[N];
int L2[N],R2[N],f2[N],sum2[N];
int n,m,cnt,t1,t2,tot1,tot2,qnt;
struct Node{int op,x,t,id;}P[N];
bool cmp(Node A,Node B){return A.t<B.t;}
int Find(int x,int fa[]){return x==fa[x]?x:fa[x]=Find(fa[x],fa);}
void DFS1(int x){L1[x]=inf;R1[x]=-inf;if(x<=n){L1[x]=R1[x]=++t1;}for(auto y:G1[x]){DFS1(y);L1[x]=min(L1[x],L1[y]);R1[x]=max(R1[x],R1[y]);}}
void DFS2(int x){L2[x]=inf;R2[x]=-inf;if(x<=n){L2[x]=R2[x]=++t2;}for(auto y:G2[x]){DFS2(y);L2[x]=min(L2[x],L2[y]);R2[x]=max(R2[x],R2[y]);}}
void Merge1(int x,int y){x=Find(x,f1);y=Find(y,f1);if(x!=y){f1[x]=f1[y]=++tot1;sum1[tot1]=sum1[x]+sum1[y];G1[tot1].push_back(x);G1[tot1].push_back(y);}}
void Merge2(int x,int y){x=Find(x,f2);y=Find(y,f2);if(x!=y){f2[x]=f2[y]=++tot2;sum2[tot2]=sum2[x]+sum2[y];G2[tot2].push_back(x);G2[tot2].push_back(y);}}
struct Segment_Tree{
	int t[N*4];
	void Pushdown(int p){if(t[p]){t[p<<1]=t[p<<1|1]=t[p];t[p]=0;}}
	void Update(int x,int y,int tim,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){t[p]=tim;return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,tim,lson);Update(x,y,tim,rson);
	}
	int Query(int x,int p,int l,int r){
		if(l==r||t[p])return t[p];
		int mid=(l+r)>>1;Pushdown(p);
		return (x<=mid?Query(x,lson):Query(x,rson));
	}
}Tree;
struct BIT{
	ll c[N];
	int lowbit(int x){return x&(-x);}
	void Add(int x,int y){for(;x<=n;x+=lowbit(x))c[x]+=y;}
	ll Ask(int x){ll ans=0;for(;x>=1;x-=lowbit(x))ans+=c[x];return ans;}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();tot1=tot2=n;
	for(int i=1;i<=n*2;i++)f1[i]=f2[i]=i;
	for(int i=1;i<=n;i++)sum1[i]=sum2[i]=1;
	for(int i=1;i<=m;i++){
		scanf("%s",s);
		if(s[0]=='U')Merge1(read(),read());
		if(s[0]=='M')Merge2(read(),read());
		if(s[0]=='A'){int x=Find(read(),f1);P[++cnt]=(Node){1,x,i,0};}
		if(s[0]=='Z'){int x=Find(read(),f2);P[++cnt]=(Node){2,x,i,0};}
		if(s[0]=='Q'){int x=read();P[++cnt]=(Node){3,x,i,++qnt};}
	}
	for(int i=1;i<=tot1;i++)if(f1[i]==i)DFS1(i);
	for(int i=1;i<=tot2;i++)if(f2[i]==i)DFS2(i);
	for(int i=1;i<=cnt;i++){
		if(P[i].op==2)Tree.Update(L2[P[i].x],R2[P[i].x],P[i].t,1,1,n);
		if(P[i].op==3)P[++cnt]=(Node){4,P[i].x,Tree.Query(L2[P[i].x],1,1,n),P[i].id};
	}
	sort(P+1,P+cnt+1,cmp);
	for(int i=1;i<=cnt;i++){
		if(P[i].op==1){
			tree.Add(L1[P[i].x],sum1[P[i].x]);
			tree.Add(R1[P[i].x]+1,-sum1[P[i].x]);
		}
		if(P[i].op==3)Ans[P[i].id]+=tree.Ask(L1[P[i].x]);
		if(P[i].op==4)Ans[P[i].id]-=tree.Ask(L1[P[i].x]);
	}
	for(int i=1;i<=qnt;i++)printf("%lld\n",Ans[i]);
	return 0;
}
