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
const int N=2005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,Ans,a[N],b[N],f[N][N],g[N],fac[N];
struct BIT{
	int c[N];
	int lowbit(int x){return x&(-x);}
	void Add(int x,int y){for(;x<=n;x+=lowbit(x))c[x]=(c[x]+y)%Mod;}
	int Ask(int x){int ans=0;for(;x>=1;x-=lowbit(x))ans=(ans+c[x])%Mod;return ans;}
}tree[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=b[i]=read();
	sort(b+1,b+n+1);b[0]=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++){
		f[i][1]=1;
		a[i]=lower_bound(b+1,b+b[0]+1,a[i])-b;
		for(int j=i;j>=1;j--){
			f[i][j]=(f[i][j]+tree[j-1].Ask(a[i]))%Mod;
			tree[j].Add(a[i],f[i][j]);
			g[j]=(g[j]+f[i][j])%Mod;
		}
	}
	fac[0]=fac[1]=1;
	for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%Mod;
	for(int i=1;i<=n;i++){
		Ans=(Ans+1ll*g[i]*fac[n-i]%Mod-1ll*g[i+1]*fac[n-i-1]%Mod*(i+1)%Mod+Mod)%Mod;
	}
	printf("%d",Ans);
	return 0;
}