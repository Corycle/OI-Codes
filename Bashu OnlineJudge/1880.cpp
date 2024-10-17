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
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int L[N],R[N];
int n,m,Ans,Num,Sum;
struct Node{int x,y;}P[N];
bool cmp(Node A,Node B){return A.x<B.x;}
int F(int x){return 1ll*(x+1)*x/2%Mod;}
int mod(int x){return x>=Mod?x-Mod:x;}
struct Tree{int v1,v2,s1,s2,tag;};
struct Segment_Tree{
	Tree t[N*4];
	void update(int p,int x){
		t[p].tag=mod(t[p].tag+x);
		t[p].s1=mod(t[p].s1+1ll*x*t[p].v1%Mod);
		t[p].s2=mod(t[p].s2+1ll*x*t[p].v2%Mod);
	}
	void Pushdown(int p){if(t[p].tag){update(p<<1,t[p].tag);update(p<<1|1,t[p].tag);t[p].tag=0;}}
	void Pushup(int p){t[p].s1=mod(t[p<<1].s1+t[p<<1|1].s1);t[p].s2=mod(t[p<<1].s2+t[p<<1|1].s2);}
	void Build(int p,int l,int r){
		t[p].v1=r-l+1;t[p].v2=mod(F(r)-F(l-1)+Mod);
		if(l==r)return;int mid=(l+r)>>1;Build(lson);Build(rson);
	}
	void Update(int x,int y,int val,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,val);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,val,lson);Update(x,y,val,rson);Pushup(p);
	}
	void Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){Num=mod(Num+t[p].s1)%Mod;Sum=mod(Sum+t[p].s2)%Mod;return;}
		int mid=(l+r)>>1;Pushdown(p);Query(x,y,lson);Query(x,y,rson);
	}
}tree;
void Update(int x,int val){tree.Update(L[x],R[x],val,1,1,n);}
void Query(int x){Sum=Num=0;tree.Query(L[x],R[x],1,1,n);}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){P[i].x=read()+1;P[i].y=read()+1;}
	sort(P+1,P+n+1,cmp);L[0]=inf;
	for(int i=1;i<=n;i++)L[i]=min(L[i-1],P[i].y);
	for(int i=n;i>=1;i--)R[i]=max(R[i+1],P[i+1].y-1);
	tree.Build(1,1,n);
	for(int i=1,j=1;i<n;i++){
		while(L[j]>R[i])Update(j++,Mod-1);
		Update(i,1);Query(i);
		Ans=mod(Ans+mod(1ll*Num*(R[i]+1)%Mod-Sum+Mod));
	}
	printf("%d\n",Ans);
	return 0;
}
