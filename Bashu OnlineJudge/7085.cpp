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
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,c,cnt,Ans;
int a[N],h[N],fac[N],inv[N],f[N][2];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
int mod(int x){return x>=Mod?x-Mod:x;}
int Pow(int x,int y){
	int ans=1;
	while(y){if(y&1)ans=1ll*ans*x%Mod;x=1ll*x*x%Mod;y>>=1;}
	return ans;
}
void Prepare(){
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(int i=2;i<N;i++)fac[i]=1ll*fac[i-1]*i%Mod;
	for(int i=2;i<N;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<N;i++)inv[i]=1ll*inv[i-1]*inv[i]%Mod;
}
int C(int n,int m){return n<m?0:1ll*fac[n]*inv[m]%Mod*inv[n-m]%Mod;}
namespace Task1{
	int col[N],num[N];
	void Solve(){
		for(int x=1;x<=n;x++){
			for(int i=h[x];i;i=d[i].next){
				if(col[x]==col[d[i].to])return;
			}
		}
		for(int i=1;i<=c;i++)num[i]=0;
		for(int i=1;i<=n;i++)if(a[i]){if(!num[col[i]])Ans++;num[col[i]]++;}
	}
	void DFS(int x){
		if(x==n+1){Solve();return;}
		for(int i=1;i<=c;i++){col[x]=i;DFS(x+1);}
	}
	void Main(){DFS(1);printf("%d\n",Ans);}
}
void DFS(int x,int fa){
	f[x][0]=1;f[x][1]=a[x]^1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;
		DFS(y,x);
		f[x][0]=1ll*f[x][0]*mod(1ll*f[y][0]*(c-2)%Mod+f[y][1])%Mod;
		f[x][1]=1ll*f[x][1]*f[y][0]%Mod*(c-1)%Mod;
	}
}
int main(){
//	freopen("color.in","r",stdin);
//	freopen("color.out","w",stdout);
	n=read();c=read();m=read();Prepare();
	for(int i=1;i<n;i++){int x=read(),y=read();Add(x,y);Add(y,x);}
	for(int i=1;i<=m;i++)a[read()]=1;
	if(n<=5&&c<=5){Task1::Main();return 0;}
	if(m==1){Ans=1ll*c*Pow(c-1,n-1)%Mod;printf("%d\n",Ans);return 0;}
	if(m==n){Ans=1ll*c*mod(1ll*c*Pow(c-1,n-1)%Mod-1ll*(c-1)*Pow(c-2,n-1)%Mod+Mod)%Mod;printf("%d\n",Ans);return 0;}
	DFS(1,0);Ans=1ll*c*mod(1ll*c*Pow(c-1,n-1)%Mod-mod(1ll*(c-1)*f[1][0]%Mod+f[1][1])+Mod)%Mod;printf("%d\n",Ans);
	return 0;
}