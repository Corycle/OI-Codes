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
const int Mod=1e9+7;
const int N=2e5+5;
const int M=12;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,K;
int f[M],g[M],S[M][M];
struct Line{int l,r;}P[N];
int mod(int x){return x>=Mod?x-Mod:x;}
bool cmp(Line A,Line B){return A.l<B.l;}
void Prepare(){
	S[0][0]=1;
	for(int i=0;i<=K;i++){
		for(int j=1;j<=i;j++){
			S[i][j]=mod(S[i-1][j-1]+1ll*j*S[i-1][j]%Mod);
		}
	}
}
struct Tree{int a[M],tag;};
struct Segment_Tree{
	Tree t[N*4];
	void update(int p,int x){
		t[p].tag=1ll*t[p].tag*x%Mod;
		for(int i=0;i<=K;i++)t[p].a[i]=1ll*t[p].a[i]*x%Mod;
	}
	void Pushdown(int p){
		if(t[p].tag!=1){
			update(p<<1,t[p].tag);
			update(p<<1|1,t[p].tag);
			t[p].tag=1;
		}
	}
	void Build(int p,int l,int r){
		t[p].tag=1;
		if(l==r)return;
		int mid=(l+r)>>1;
		Build(lson);Build(rson);
	}
	void Update1(int x,int g[],int p,int l,int r){
		for(int i=0;i<=K;i++)t[p].a[i]=mod(t[p].a[i]+g[i]);
		if(l==r)return;
		int mid=(l+r)>>1;Pushdown(p);
		if(x<=mid)Update1(x,g,lson);
		if(x>mid) Update1(x,g,rson);
	}
	void Update2(int x,int y,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,2);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update2(x,y,lson);Update2(x,y,rson);
		for(int i=0;i<=K;i++)t[p].a[i]=mod(t[p<<1].a[i]+t[p<<1|1].a[i]);
	}
	void Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){for(int i=0;i<=K;i++)g[i]=mod(g[i]+t[p].a[i]);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Query(x,y,lson);Query(x,y,rson);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();K=1;Prepare();
	for(int i=1;i<=n;i++){
		P[i].l=read();
		P[i].r=read();
	}
	sort(P+1,P+n+1,cmp);
	g[0]=1;
	tree.Build(1,0,n*2);
	tree.Update1(0,g,1,0,n*2);
	for(int i=1;i<=n;i++){
		memset(g,0,sizeof(g));
		tree.Query(0,P[i].l-1,1,0,n*2);
		f[0]=g[0];
		for(int i=1;i<=K;i++)f[i]=mod(g[i-1]+g[i]);
		
		memset(g,0,sizeof(g));
		tree.Query(P[i].l,P[i].r,1,0,n*2);
		for(int i=0;i<=K;i++)f[i]=mod(f[i]+g[i]);
		
		tree.Update1(P[i].r,f,1,0,n*2);
		tree.Update2(P[i].r+1,n*2,1,0,n*2);
	}
	int Ans=0,Fac=1;
	for(int i=0;i<=K;i++){
		if(i)Fac=1ll*Fac*i%Mod;
		Ans=mod(Ans+1ll*Fac*S[K][i]%Mod*tree.t[1].a[i]%Mod);
	}
	printf("%d",Ans);
	return 0;
}