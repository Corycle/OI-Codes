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
const int N=1e5+15;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[10];
int n,m,Q,Max,a[N],b[N],fac[N],inv[N];
int mod(int x){return x>=Mod?x-Mod:x;}
void Prepare(){
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(int i=2;i<N;i++)fac[i]=1ll*fac[i-1]*i%Mod;
	for(int i=2;i<N;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<N;i++)inv[i]=1ll*inv[i-1]*inv[i]%Mod;
}
int C(int n,int m){
	int f=1;
	if(n<0){f=(m&1)?Mod-1:1;n=m-n-1;}
	return n<m?0:1ll*fac[n]*inv[m]%Mod*inv[n-m]%Mod*f%Mod;
}
struct BIT{
	int c[N];
	int lowbit(int x){return x&(-x);}
	void Add(int x,int y){for(;x<=Max;x+=lowbit(x))c[x]=mod(c[x]+y);}
	int Ask(int x){int ans=0;for(;x>=1;x-=lowbit(x))ans=mod(ans+c[x]);return ans;}
	int Query(int l,int r){return mod(Ask(r)-Ask(l-1)+Mod);}
}Rtree[11],Ctree[11];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Q=read();Max=max(n,m);Prepare();
	for(int i=1;i<=n;i++)a[i]=i-1;
	for(int i=1;i<=m;i++)b[i]=i;
	for(int j=0;j<=10;j++){
		for(int i=1;i<=n;i++)Rtree[j].Add(i,1ll*a[i]*C(-i,j)%Mod);
		for(int i=1;i<=m;i++)Ctree[j].Add(i,1ll*b[i]*C(-i,j)%Mod);
	}
	while(Q--){
		scanf("%s",s);
		if(s[0]=='R'){
			int x=read(),y=read();
			for(int j=0;j<=10;j++){
				Rtree[j].Add(x,1ll*mod(a[y]-a[x]+Mod)*C(-x,j)%Mod);
				Rtree[j].Add(y,1ll*mod(a[x]-a[y]+Mod)*C(-y,j)%Mod);
			}
			swap(a[x],a[y]);
		}
		if(s[0]=='C'){
			int x=read(),y=read();
			for(int j=0;j<=10;j++){
				Ctree[j].Add(x,1ll*mod(b[y]-b[x]+Mod)*C(-x,j)%Mod);
				Ctree[j].Add(y,1ll*mod(b[x]-b[y]+Mod)*C(-y,j)%Mod);
			}
			swap(b[x],b[y]);
		}
		if(s[0]=='Q'){
			int sx=read(),sy=read(),tx=read(),ty=read(),k=read();
			int ans1=0,ans2=0;
			for(int j=0;j<=k;j++){
				ans1=mod(ans1+1ll*C(tx+k,k-j)*Rtree[j].Query(sx,tx)%Mod);
				ans2=mod(ans2+1ll*C(ty+k,k-j)*Ctree[j].Query(sy,ty)%Mod);
			}
			int Ans=mod(1ll*ans1*C(ty-sy+k+1,k+1)%Mod*m%Mod+1ll*ans2*C(tx-sx+k+1,k+1)%Mod);
			printf("%d\n",Ans);
		}
	}
	return 0;
}