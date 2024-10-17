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
const ll N=2005;
const ll M=105;
const ll P=15;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,ans,maxn;
ll num[N*M],p[N][N],f[P][N][M];
void dfs(ll x,ll y,ll l,ll k,ll a,ll b){
	if(l>n){
		p[x][y]=p[y][x]=1;
		num[x]=a;num[y]=b;
		return;
	}
	dfs(x<<1,y<<1,l+1,0,a,b);
	if(k==0){
		dfs(x<<1|1,y<<1,l+1,1,a+1,b);
		dfs(x<<1,y<<1|1,l+1,1,a,b+1);
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	while(scanf("%lld%lld",&n,&m)!=EOF){
		memset(num,0,sizeof(num));
		memset(f,0,sizeof(f));
		memset(p,0,sizeof(p));
		ans=0;maxn=(1<<n);
		dfs(0,0,1,0,0,0);
		for(ll i=0;i<maxn;i++)f[1][i][num[i]]=1;
		for(ll i=1;i<=n;i++){
			for(ll j=0;j<maxn;j++){
				for(ll k=0;k<maxn;k++){
					if(!p[j][k])continue;
					for(ll sum=num[k];sum<=m;sum++){
						if(sum+num[j]>m)continue;
						f[i][j][sum+num[j]]+=f[i-1][k][sum];
					}
				}
				if(i==n)ans+=f[i][j][m];
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}