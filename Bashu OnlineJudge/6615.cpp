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
using namespace std;
const int inf=0x3f3f3f3f;
const int Maxn=1e9+5;
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot,Ans,Max,a[N],b[N],c[N];
struct Node{int l,r,val;}P[N];
int main(){
//	freopen("lucky.in","r",stdin);
//	freopen("lucky.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		int op=read();
		if(op==1){int l=read(),r=read();P[++m]=(Node){l,r,read()};}
		if(op==2){int x=read(),y=read();P[++m]=(Node){x,x,y};}
		if(op==3){int x=read(),y=read();P[++m]=(Node){-Maxn,x-1,y};P[++m]=(Node){x+1,Maxn,y};}
	}
	b[++tot]=0;
	for(int i=1;i<=m;i++){
		b[++tot]=P[i].l;b[++tot]=P[i].l-1;
		b[++tot]=P[i].r;b[++tot]=P[i].r+1;
	}
	sort(b+1,b+tot+1);tot=unique(b+1,b+tot+1)-b-1;
	for(int i=1;i<=m;i++){
		P[i].l=lower_bound(b+1,b+tot+1,P[i].l)-b;
		P[i].r=lower_bound(b+1,b+tot+1,P[i].r)-b;
		c[P[i].l]^=P[i].val;c[P[i].r+1]^=P[i].val;
	}
	Max=-inf;
	for(int i=1;i<=tot;i++){
		c[i]^=c[i-1];
		if(c[i]>Max){Max=c[i];Ans=b[i];}
		if(c[i]==Max)Ans=(abs(Ans)<abs(b[i])?Ans:b[i]);
	}
	printf("%d %d\n",Max,Ans);
	return 0;
}