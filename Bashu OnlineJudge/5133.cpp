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
const int Mod=1e9+7;
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
int n,m,b[N],fa[N];
struct Line{int l,r;}P[N];
bool cmp(Line A,Line B){
	return (A.r-A.l+1)<(B.r-B.l+1);
}
int Find(int x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
int main(){
//	freopen("steins.in","r",stdin);
//	freopen("steins.out","w",stdout);
	int T=read();
	while(T--){
		int Ans=0;b[0]=0;
		m=read();n=read();
		for(int i=1;i<=n;i++){
			b[++b[0]]=P[i].l=read();
			b[++b[0]]=P[i].r=read()+1;
		}
		sort(b+1,b+b[0]+1);
		b[0]=unique(b+1,b+b[0]+1)-b-1;
		for(int i=1;i<=b[0];i++)fa[i]=i;
		for(int i=1;i<=n;i++){
			P[i].l=lower_bound(b+1,b+b[0]+1,P[i].l)-b;
			P[i].r=lower_bound(b+1,b+b[0]+1,P[i].r)-b;
		}
		sort(P+1,P+n+1,cmp);
		for(int i=1;i<=n;i++){
			int x=Find(P[i].l);
			int y=Find(P[i].r);
			if(x!=y){Ans++;fa[x]=y;}
		}
		printf("%d\n",Pow(2,Ans));
	}
	return 0;
}