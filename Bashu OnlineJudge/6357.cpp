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
const int Mod=1e9+7;
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
namespace io {
	const int SIZE = (1 << 21) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55]; int f, qr;
	// getchar
	#define gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	// print the remaining part
	inline void flush () {
		fwrite (obuf, 1, oS - obuf, stdout);
		oS = obuf;
	}
	// putchar
	inline void putc (char x) {
		*oS ++ = x;
		if (oS == oT) flush ();
	}
	// input a signed integer
	template <class I>
	inline void gi (I &x) {
		for (f = 1, c = gc(); c < '0' || c > '9'; c = gc()) if (c == '-') f = -1;
		for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15); x *= f;
	}
	// print a signed integer
	template <class I>
	inline void print (I x) {
		if (!x) putc ('0'); if (x < 0) putc ('-'), x = -x;
		while (x) qu[++ qr] = x % 10 + '0',  x /= 10;
		while (qr) putc (qu[qr --]);
	}
	//no need to call flush at the end manually!
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
}
using io :: gi;
using io :: putc;
using io :: print;

int n,m;
struct Node{int l,r,val;}P[N];
bool cmp(Node A,Node B){
	return A.l!=B.l?A.l<B.l:A.r<B.r;
}
int mod(int x){return x>=Mod?x-Mod:x;}
struct Segment_Tree{
	struct Tree{int tag,sum;}t[N*4];
	void update(int p,int x){
		t[p].tag=1ll*t[p].tag*x%Mod;
		t[p].sum=1ll*t[p].sum*x%Mod;
	}
	void Pushdown(int p){
		if(t[p].tag!=1){
			update(p<<1,t[p].tag);
			update(p<<1|1,t[p].tag);
			t[p].tag=1;
		}
	}
	void Add(int x,int y,int p,int l,int r){
		if(x<l||x>r)return;
		if(l==r){t[p].sum=mod(t[p].sum+y);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Add(x,y,lson);Add(x,y,rson);
		t[p].sum=mod(t[p<<1].sum+t[p<<1|1].sum);
	}
	void Update(int x,int y,int z,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,z);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,z,lson);Update(x,y,z,rson);
		t[p].sum=mod(t[p<<1].sum+t[p<<1|1].sum);
	}
	int Ask(int x,int y,int p,int l,int r){
		if(y<l||x>r)return 0;
		if(x<=l&&r<=y)return t[p].sum;
		int mid=(l+r)>>1;Pushdown(p);
		return mod(Ask(x,y,lson)+Ask(x,y,rson));
	}
}tree;
int main(){
//	freopen("gugugu.in","r",stdin);
//	freopen("gugugu.out","w",stdout);
	gi(n);gi(m);
	for(int i=1;i<=m;i++){
		gi(P[i].l);
		gi(P[i].r);
		gi(P[i].val);
	}
	sort(P+1,P+m+1,cmp);
	for(int i=1;i<=m;i++){
		int tmp=tree.Ask(max(P[i].l-1,1),P[i].r,1,1,n);
		if(P[i].l==1)tmp=mod(tmp+1);
		tree.Add(P[i].r,1ll*tmp*P[i].val%Mod,1,1,n);
		if(P[i].r<n)tree.Update(P[i].r+1,n,mod(P[i].val+1),1,1,n);
	}
	printf("%d",tree.Ask(n,n,1,1,n));
	return 0;
}