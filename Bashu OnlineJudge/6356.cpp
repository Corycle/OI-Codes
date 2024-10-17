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
using namespace std;
const int inf=0x3f3f3f3f;
const int Mod=1e9+7;
const int N=3005;
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

int n,m,P;
int f[N][N],g[N][N];
int mod(int x){return x>=Mod?x-Mod:x;}
int main(){
//	freopen("gugu.in","r",stdin);
//	freopen("gugu.out","w",stdout);
	gi(n);gi(m);gi(P);
	while(P--){
		int sx=0,sy=0;
		int tx=0,ty=0;
		gi(sx);gi(sy);
		gi(tx);gi(ty);
		if(g[sx][sy]){
			if(sx+1==tx&&sy==ty&&g[sx][sy]==2)g[sx][sy]=3;
			if(sy+1==ty&&sx==tx&&g[sx][sy]==1)g[sx][sy]=3;
		}
		else{
			if(sx+1==tx&&sy==ty)g[sx][sy]=1;//down
			if(sy+1==ty&&sx==tx)g[sx][sy]=2;//right
			if(!g[sx][sy])g[sx][sy]=3;//can't
		}
	}
	if(g[1][1]!=3)f[1][1]=1;
	for(int i=2;i<=n;i++){
		if(g[i-1][1]==2||g[i][1]==3)break;
		f[i][1]=mod(f[i][1]+f[i-1][1]);
	}
	for(int i=2;i<=m;i++){
		if(g[1][i-1]==1||g[1][i]==3)break;
		f[1][i]=mod(f[1][i]+f[1][i-1]);
	}
	for(int i=2;i<=n;i++){
		for(int j=2;j<=m;j++){
			if(g[i-1][j]!=2&&g[i-1][j]!=3)f[i][j]=mod(f[i][j]+f[i-1][j]);
			if(g[i][j-1]!=1&&g[i][j-1]!=3)f[i][j]=mod(f[i][j]+f[i][j-1]);
		}
	}
	printf("%d",f[n][m]);
	return 0;
}