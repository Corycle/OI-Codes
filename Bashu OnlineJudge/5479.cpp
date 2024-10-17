#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
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
const ll Mod=998244353;
const ll M=505;
const ll N=35;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,top,ans,a[N][N],b[N][N];
ll sx[N],sy[N],cnt[M],f[N][M];
ll dx[8]={0,1,0,-1,1,-1,1,-1};
ll dy[8]={1,0,-1,0,1,1,-1,-1};
ll DP(){
	top=0;
	memset(f,0,sizeof(f));
	memset(cnt,0,sizeof(cnt));
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=m;j++){
			if(a[i][j]){
				top++;
				sx[top]=i;
				sy[top]=j;
			}
		}
	}
	ll S=1<<top;
	for(ll i=0;i<S;i++){
		memset(b,0,sizeof(b));
		for(ll j=0;j<top;j++){
			if(!((i>>j)&1)){
				for(ll k=0;k<8;k++){
					ll fx=sx[j+1]+dx[k],fy=sy[j+1]+dy[k];
					if(fx<1||fx>n||fy<1||fy>m)continue;
					b[fx][fy]=1;
				}
				b[sx[j+1]][sy[j+1]]=1;
			}
		}
		for(ll x=1;x<=n;x++){
			for(ll y=1;y<=m;y++){
				cnt[i]+=(!b[x][y]);
			}
		}
	}
	f[0][0]=1;
	for(ll i=1;i<=n*m;i++){
		for(ll j=0;j<S;j++){
			f[i][j]=(f[i][j]+f[i-1][j]*max(cnt[j]-i+1,0ll)%Mod)%Mod;
			for(ll k=0;k<top;k++){
				if((j>>k)&1)f[i][j]=(f[i][j]+f[i-1][j-(1<<k)])%Mod;
			}
		}
	}
	return f[n*m][S-1];
}
void DFS(ll x,ll y,ll z){
	if(y==m+1){DFS(x+1,1,z);return;}
	if(x==n+1){ans=(ans+DP()*z)%Mod;return;}
	DFS(x,y+1,z);
	ll flag=(!a[x][y]);
	for(ll i=0;i<8;i++){
		ll fx=x+dx[i],fy=y+dy[i];
		if(fx<1||fx>n||fy<1||fy>m)continue;
		if(a[fx][fy]){flag=0;break;}
	}
	if(flag){a[x][y]=1;DFS(x,y+1,-z);a[x][y]=0;}
}
char s[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	while(scanf("%lld%lld",&n,&m)!=EOF){
		int flag=0;
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		for(ll i=1;i<=n;i++){
			scanf("%s",s+1);
			for(ll j=1;j<=m;j++){
				if(s[j]=='X'){
					a[i][j]=1;
					for(ll k=0;k<8;k++){
						if(a[i+dx[k]][j+dy[k]])flag=1;
					}
				}
			}
		}
		if(flag){puts("0");continue;}
		ans=0;DFS(1,1,1);
		printf("%lld\n",(ans%Mod+Mod)%Mod);
	}
	return 0;
}