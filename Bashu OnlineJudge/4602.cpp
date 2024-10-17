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
#define pii pair<ll,ll>
#define fst first
#define scd second
#define mp make_pair
using namespace std;
const int inf=0x3f3f3f3f;
const int st=300;
const int M=605;
const int N=55;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll L,R,K,P,V,c[N],f[N][M],g[N][M];
pii DFS(int x,ll val,int flag){
	if(!x){val-=st;return mp(0,(-V<=val&&val<V));}
	if(!flag&&f[x][val]!=-1)return mp(f[x][val],g[x][val]);
	int k=flag?c[x]:K-1;ll ans=0,num=0;
	if(x==P){
		if(k<V)return mp(0,0);
		return DFS(x-1,val,flag&(V==k));
	}
	for(int i=0;i<=k;i++){
		if(x>P){pii tmp=DFS(x-1,val+i,flag&(i==k));ans+=tmp.fst+tmp.scd*i*(x-P);num+=tmp.scd;}
		if(x<P){pii tmp=DFS(x-1,val-i,flag&(i==k));ans+=tmp.fst+tmp.scd*i*(P-x);num+=tmp.scd;}
	}
	if(!flag){f[x][val]=ans;g[x][val]=num;}
	return mp(ans,num);
}
ll Ask(ll n){
	ll ans=0;c[0]=0;
	while(n){c[++c[0]]=n%K;n/=K;}
	for(int i=1;i<=c[0];i++){
		for(int j=0;j<K;j++){
			memset(f,-1,sizeof(f));
			memset(g,-1,sizeof(g));
			P=i;V=j;ans+=DFS(c[0],st,1).fst;
		}
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	L=read();R=read();K=read();
	printf("%lld",Ask(R)-Ask(L-1));
	return 0;
}