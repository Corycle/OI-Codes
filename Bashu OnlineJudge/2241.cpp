#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll Mod=1e9+7;
const ll M=100005;
const ll N=25;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m;
char s[N],c[N]="ACGT";
ll f[M],g[M],p[M],ans[M],t[M][N];
ll lowbit(ll x){return x&(-x);}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	for(ll i=1;i<32768;i++){
		p[i]=p[i-lowbit(i)]+1;
		//i二进制1的个数 
	}
	ll T=read();
	while(T--){
		scanf("%s",s+1);
		n=strlen(s+1);m=read();
		memset(f,0,sizeof(f));
		memset(t,0,sizeof(t));
		memset(ans,0,sizeof(ans));
		for(ll i=0;i<32768;i++){
			for(ll j=0;j<4;j++){
				ll x=0,y=0;
				for(ll k=1;k<=n;k++){
					ll fy=y+((i>>(k-1))&1);
					ll fx=max(x,fy);
					if(s[k]==c[j])fx=max(fx,y+1);
					if(fx>x)t[i][j]+=(1<<(k-1));
					x=fx;y=fy;
				}
			}
		}
		//t[j][k]表示从j状态加一个字母k转移到的状态
		f[0]=1;
		for(ll i=1;i<=m;i++){
			memset(g,0,sizeof(g));
			for(ll j=0;j<32768;j++){
				for(ll k=0;k<4;k++){
					g[t[j][k]]=(g[t[j][k]]+f[j])%Mod;
					//f[i][t[j][k]]+=f[i-1][j]
				}
			}
			memcpy(f,g,sizeof(f));
		}
		for(ll i=0;i<32768;i++)ans[p[i]]=(ans[p[i]]+f[i])%Mod;
		for(ll i=0;i<=n;i++)printf("%lld\n",ans[i]);
	}
	return 0;
}