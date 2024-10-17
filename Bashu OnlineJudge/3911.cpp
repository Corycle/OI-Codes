#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll Mod=1999997;
const ll Mul=1433;
const ll P=2000005;
const ll N=100005;
const ll M=10;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,cnt;
ll h[P],a[N][M],C[M][M];
struct Line{
	ll to,next,sum;
}d[P];
void Add(ll x,ll y){
	d[++cnt]=(Line){y,h[x],1};
	h[x]=cnt;
}
bool Check(ll x,ll y,ll s){
	for(ll i=1;i<=6;i++){
		if(s&(1<<(i-1))&&a[x][i]!=a[y][i])return false;
	}
	return true;
}
ll Ask(ll s){
	ll ans=0;cnt=0;
	memset(h,0,sizeof(h));
	for(ll i=1;i<=n;i++){
		ll x=0,p=0;
		for(ll j=1;j<=6;j++){//Hash
			if(s&(1<<(j-1)))x=(x*Mul+a[i][j])%Mod;
		}
		for(p=h[x];p;p=d[p].next){
			if(Check(d[p].to,i,s)){
				ans+=d[p].sum++;
				break;//1+2+3+4+...+(n-1)
			}
		}
		if(!p)Add(x,i);
	}
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=6;j++){
			a[i][j]=read();
		}
	}
	C[0][0]=1;
	for(ll i=1;i<=6;i++){
		C[i][0]=1;
		for(ll j=1;j<=6;j++){
			C[i][j]=C[i-1][j]+C[i-1][j-1];
		}
	}
	ll Sta=(1<<6)-1,ans=0;
	for(ll s=0;s<=Sta;s++){
		ll num=0;
		for(ll i=1;i<=6;i++){
			if(s&(1<<(i-1)))num++;
		}
		if(num>=m){
			ll dlt=Ask(s)*C[num][m];
			ans+=(num-m)&1?-dlt:dlt;
		}
	}
	printf("%lld\n",ans);
	return 0;
}