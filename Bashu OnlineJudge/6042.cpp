#include<bits/stdc++.h>
#define ll long long
#define re register
#define ull unsigned ll
using namespace std;
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
const int N=1e5+5;
const int Inf=(1<<30);
int n,Ans;
int Lg[N],d[N],f[N],e[N],p[N][17],w[N][17];
int Read(){int x;gi(x);return (x+Ans)%n+1;}
inline int Get(int x){
	if(f[x]==x)return x;
	int fx=Get(f[x]);
	e[x]+=d[f[x]]-d[fx];
	return d[x]=d[fx]+e[x],f[x]=fx;
}
int Pre(int x,int k){
	if(p[x][k])return p[x][k];
	p[x][k]=Pre(Pre(x,k-1),k-1);
	w[x][k]=min(w[x][k-1],w[p[x][k-1]][k-1]);
	return p[x][k];
}
int Find(int x,int k){
	for(int i=Lg[k];i>=0;i--)
	if(k>>i&1)Pre(x,i),Ans=min(Ans,w[x][i]),x=p[x][i];
	return x;
}
int main(){
//	freopen("money.in","r",stdin);
//	freopen("money.out","w",stdout);
	gi(n);
	for(int i=2;i<=n;i++)Lg[i]=Lg[i>>1]+1;
	for(int i=1;i<=n;i++)f[i]=i,d[i]=1;
	int T;gi(T);
	while(T--){
		int op,a,b;
		gi(op),a=Read(),b=Read();
		if(op==0)p[a][0]=f[a]=b,e[a]=1,w[a][0]=Read();
		else{
			Ans=Inf,Get(a),Get(b);
			if(d[a]<=d[b]||Find(a,d[a]-d[b])!=b)Ans=0;
			print(Ans);putc('\n');
		}
	}
	return 0;
}