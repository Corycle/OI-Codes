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
const int M=61;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll f[M];
int n,m,Flag,a[N],c[N],tmp[M];
int mod(int x){return x>m?x-m:x;}
struct Tree{
	int Max[M],tag1,tag2;
	void Init(){
		tag1=tag2=0;
		for(int i=1;i<=m;i++)Max[i]=-inf;
	}
	friend Tree operator+(Tree A,Tree B){
		Tree C;C.Init();
		for(int i=1;i<=m;i++)C.Max[i]=max(A.Max[i],B.Max[i]);
		return C;
	}
};
Tree Ans;
struct Segment_Tree{
	Tree t[N*4];
	void update1(int p,int d){
		d%=m;
		for(int i=1;i<=m;i++)tmp[mod(i+d)]=t[p].Max[i];
		for(int i=1;i<=m;i++)t[p].Max[i]=tmp[i];
		t[p].tag1+=d;
	}
	void update2(int p,int b){
		for(int i=1;i<=m;i++)t[p].Max[i]+=b;
		t[p].tag2+=b;
	}
	void Pushdown(int p){
		if(t[p].tag1){update1(p<<1,t[p].tag1);update1(p<<1|1,t[p].tag1);t[p].tag1=0;}
		if(t[p].tag2){update2(p<<1,t[p].tag2);update2(p<<1|1,t[p].tag2);t[p].tag2=0;}
	}
	void Build(int p,int l,int r){
		t[p].Init();
		if(l==r){t[p].Max[c[l]]=a[l];return;}
		int mid=(l+r)>>1;
		Build(lson);Build(rson);
		t[p]=t[p<<1]+t[p<<1|1];
	}
	void Update1(int x,int y,int z,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update1(p,z);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update1(x,y,z,lson);Update1(x,y,z,rson);
		t[p]=t[p<<1]+t[p<<1|1];
	}
	void Update2(int x,int y,int z,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update2(p,z);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update2(x,y,z,lson);Update2(x,y,z,rson);
		t[p]=t[p<<1]+t[p<<1|1];
	}
	void Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){
			if(!Flag)Ans=t[p];
			else Ans=Ans+t[p];
			Flag=1;return;
		}
		int mid=(l+r)>>1;Pushdown(p);
		Query(x,y,lson);Query(x,y,rson);
	}
}tree;
void Query(int l,int r){
	Flag=0;tree.Query(l,r,1,1,n);
	for(int i=1;i<=m;i++)f[i]=0;
	for(int i=1;i<=m;i++){
		if(Ans.Max[i]<0)continue;
		for(int k=1;k*i<=m;k++){
			for(int j=m;j>=k*i;j--){
				f[j]=max(f[j],f[j-k*i]+1ll*k*Ans.Max[i]);
			}
		}
	}
	ll Ans1=0,Ans2=0;
	for(int i=1;i<=m;i++)Ans1+=f[i];
	for(int i=1;i<=m;i++)Ans2^=f[i];
	printf("%lld %lld\n",Ans1,Ans2);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)c[i]=read();
	for(int i=1;i<=n;i++)a[i]=read();
	tree.Build(1,1,n);
	int T=read();
	while(T--){
		int op=read(),l=read(),r=read();
		if(op==1)tree.Update1(l,r,read(),1,1,n);
		if(op==2)tree.Update2(l,r,read(),1,1,n);
		if(op==3)Query(l,r);
	}
	return 0;
}