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
int n,m;
struct Node{int l,r,id;};
int a[N],b[N],Min[N],Max[N],Ans[N];
int mod(int x){return x>=Mod?x-Mod:x;}
vector<Node>F[N*4],Q[N];
struct Tree{int val,sum,tag;};
struct Segment_Tree{
	Tree t[N*4];
	void Pushup(int p){t[p].sum=mod(t[p<<1].sum+t[p<<1|1].sum);}
	void update(int p,int v){t[p].sum=mod(t[p].sum+1ll*t[p].val*v%Mod);t[p].tag=mod(t[p].tag+v);}
	void Pushdown(int p){if(t[p].tag){update(p<<1,t[p].tag);update(p<<1|1,t[p].tag);t[p].tag=0;}}
	void Update(int x,int y,int v,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,v);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,v,lson);Update(x,y,v,rson);Pushup(p);
	}
	void Build(int p,int l,int r){
		t[p]=(Tree){0,0,0};
		if(l==r){t[p].val=b[l];return;}
		int mid=(l+r)>>1;Build(lson);Build(rson);
		t[p].val=mod(t[p<<1].val+t[p<<1|1].val);
	}
	int Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].sum;
		int mid=(l+r)>>1;Pushdown(p);
		return mod(Query(x,y,lson)+Query(x,y,rson));
	}
}t1,t2,t3,t4;
int Sum[N*4];
int Ask(int x,int y,int l,int r){
	return mod(mod(t1.Query(x,y,1,l,r)+t2.Query(x,y,1,l,r))+mod(t3.Query(x,y,1,l,r)+t4.Query(x,y,1,l,r)));
}
void Solve(int p,int l,int r){
	if(l==r){
		Sum[p]=1ll*a[l]*a[l]%Mod;
		for(auto tmp:F[p])Ans[tmp.id]=mod(Ans[tmp.id]+Sum[p]);
		return;
	}
	int mid=(l+r)>>1,L=mid+1,R=r;Min[L-1]=inf;Max[L-1]=-inf;
	for(int i=L;i<=R;i++){Min[i]=min(Min[i-1],a[i]);Max[i]=max(Max[i-1],a[i]);}
	for(int i=L;i<=R;i++)b[i]=1;t1.Build(1,L,R);
	for(int i=L;i<=R;i++)b[i]=Min[i];t2.Build(1,L,R);
	for(int i=L;i<=R;i++)b[i]=Max[i];t3.Build(1,L,R);
	for(int i=L;i<=R;i++)b[i]=1ll*Min[i]*Max[i]%Mod;t4.Build(1,L,R);
	for(int i=l;i<=r;i++)Q[i].clear();
	for(auto tmp:F[p])if((tmp.l<=mid&&tmp.r>mid)&&!(tmp.l==l&&tmp.r==r))Q[tmp.l].push_back(tmp);
	int MIN=inf,MAX=-inf;
	for(int i=mid,j=mid,k=mid;i>=l;i--){
		MIN=min(MIN,a[i]);MAX=max(MAX,a[i]);
		while(j<r&&Min[j+1]>=MIN)j++;
		while(k<r&&Max[k+1]<=MAX)k++;
		if(j<=k){
			t1.Update(L,j,1ll*MIN*MAX%Mod,1,L,R);
			t2.Update(j+1,k,MAX,1,L,R);
			t4.Update(k+1,R,1,1,L,R);
		}
		else{
			t1.Update(L,k,1ll*MIN*MAX%Mod,1,L,R);
			t3.Update(k+1,j,MIN,1,L,R);
			t4.Update(j+1,R,1,1,L,R);
		}
		for(auto tmp:Q[i])Ans[tmp.id]=mod(Ans[tmp.id]+Ask(L,tmp.r,L,R));
	}
	for(auto tmp:F[p]){
		if(tmp.l==l&&tmp.r==r)continue;
		if(tmp.l<=mid)F[p<<1].push_back((Node){tmp.l,min(tmp.r,mid),tmp.id});
		if(tmp.r>mid)F[p<<1|1].push_back((Node){max(tmp.l,mid+1),tmp.r,tmp.id});
	}
	Sum[p]=Ask(L,R,L,R);Solve(lson);Solve(rson);Sum[p]=mod(Sum[p]+mod(Sum[p<<1]+Sum[p<<1|1]));
	for(auto tmp:F[p])if(tmp.l==l&&tmp.r==r)Ans[tmp.id]=mod(Ans[tmp.id]+Sum[p]);
}
int main(){
//	freopen("sequence.in","r",stdin);
//	freopen("sequence.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++){int l=read(),r=read();F[1].push_back((Node){l,r,i});}
	Solve(1,1,n);
	for(int i=1;i<=m;i++)printf("%d\n",Ans[i]);
	return 0;
}