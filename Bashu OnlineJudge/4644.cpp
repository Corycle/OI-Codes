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
#define pii pair<int,int>
#define fst first
#define scd second
#define mp make_pair
using namespace std;
const int inf=0x3f3f3f3f;
const int N=65;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,K;
pii f[N][2][2][2];
bool vis[N][2][2][2];
int Mod,cn[N],cm[N],ck[N];
int mod(int x){return x>=Mod?x-Mod:x;}
pii DFS(int x,int f1,int f2,int f3){
	if(!x)return mp(1,0);
	if(vis[x][f1][f2][f3])return f[x][f1][f2][f3];
	int t1=(f1?cn[x]:1),t2=(f2?cm[x]:1);
	pii ans=mp(0,0);
	for(int i=0;i<=t1;i++){
		for(int j=0;j<=t2;j++){
			if(f3&&(i^j)<ck[x])continue;
			pii tmp=DFS(x-1,f1&&(i==t1),f2&&(j==t2),f3&&((i^j)==ck[x]));
			ans.fst=mod(ans.fst+tmp.fst);
			ans.scd=mod(ans.scd+tmp.scd);
			ans.scd=mod(ans.scd+(1ll<<(x-1))%Mod*(i^j)%Mod*tmp.fst%Mod);
		}
	}
	vis[x][f1][f2][f3]=1;
	return f[x][f1][f2][f3]=ans;
}
pii Query(ll n,ll m,ll K){
	memset(cn,0,sizeof(cn));
	memset(cm,0,sizeof(cm));
	memset(ck,0,sizeof(ck));
	memset(vis,0,sizeof(vis));
	while(n){cn[++cn[0]]=n&1;n>>=1;}
	while(m){cm[++cm[0]]=m&1;m>>=1;}
	while(K){ck[++ck[0]]=K&1;K>>=1;}
	int len=max(max(cn[0],cm[0]),ck[0]);
	return DFS(len,1,1,1);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		n=read();m=read();
		K=read();Mod=read();
		pii Ans=Query(n-1,m-1,K);
		printf("%d\n",mod(Ans.scd-1ll*K%Mod*Ans.fst%Mod+Mod));
	}
	return 0;
}