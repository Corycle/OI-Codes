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
const int Mod=998244353;
const int M=(1<<18)+5;
const int N=10005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,X,S,cnt,Sta;
int h[N],P[N],F[M],K[N],B[N],deg[N],num[M];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
int mod(int x){return x>=Mod?x-Mod:x;}
int Pow(int x,int y){
	int ans=1;
	while(y){if(y&1)ans=1ll*ans*x%Mod;x=1ll*x*x%Mod;y>>=1;}
	return ans;
}
void DFS(int x,int fa){
	K[x]=B[x]=0;
	if(S&(1<<(x-1)))return;
	int SumK=0,SumB=0;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;
		DFS(y,x);
		SumK=mod(SumK+K[y]);
		SumB=mod(SumB+B[y]);
	}
	int tmp=Pow(1-1ll*P[x]*SumK%Mod+Mod,Mod-2);
	K[x]=1ll*tmp*P[x]%Mod;
	B[x]=1ll*tmp*mod(1ll*P[x]*SumB%Mod+1)%Mod;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();X=read();Sta=(1<<n)-1;
	for(int i=1;i<n;i++){int x=read(),y=read();Add(x,y);Add(y,x);deg[x]++;deg[y]++;}
	for(int i=1;i<=n;i++)P[i]=Pow(deg[i],Mod-2);
	for(S=1;S<=Sta;S++){num[S]=num[S>>1]+(S&1);DFS(X,X);F[S]=1ll*(num[S]&1?1:Mod-1)*B[X]%Mod;}
	for(int i=1;i<=n;i++)for(S=0;S<=Sta;S++)if((S>>(i-1))&1)F[S]=mod(F[S]+F[S^(1<<(i-1))]);
	while(m--){int num=read();S=0;while(num--)S|=(1<<(read()-1));printf("%d\n",F[S]);}
	return 0;
}