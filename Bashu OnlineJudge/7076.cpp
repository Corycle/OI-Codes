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
const int N=2e6+5;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
int n,m,cnt,Ans;
int h[N],fa[N],sum[N],fac[N],inv[N];
struct edge{int to,next;}d[N];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void DFS(int x,int depth){sum[depth]++;for(int i=h[x];i;i=d[i].next)DFS(d[i].to,depth+1);}
int mod(int x){return x>=Mod?x-Mod:x;}
void Prepare(){
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(int i=2;i<N;i++)fac[i]=1ll*fac[i-1]*i%Mod;
	for(int i=2;i<N;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<N;i++)inv[i]=1ll*inv[i-1]*inv[i]%Mod;
}
int C(int n,int m){return n<m?0:1ll*fac[n]*inv[m]%Mod*inv[n-m]%Mod;}
int main(){
//	freopen("deconstruct.in","r",stdin);
//	freopen("deconstruct.out","w",stdout);
	n=read();Prepare();
	for(int i=2;i<=n;i++){fa[i]=read();Add(fa[i],i);}
	DFS(1,0);
	for(int i=n-1;i>=1;i--){
		sum[i]+=sum[i+1];
		Ans=mod(Ans+1ll*sum[i]*C(n-1,i)%Mod*fac[i-1]%Mod*fac[n-1-i]%Mod);
	}
	Ans=1ll*Ans*inv[n-1]%Mod;
	printf("%d\n",Ans);
	return 0;
}