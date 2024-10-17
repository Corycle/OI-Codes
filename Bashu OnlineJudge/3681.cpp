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
const ll Mod=1000000007;
const ll N=20005;
const ll M=20;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,cnt,tot,ans;
ll p[M],c[N],num[M],v[M][N],f[M][N][2];
struct node{ll x,y;};
map<ll,ll>pos;
priority_queue<node>q;
bool operator<(node A,node B){
	return c[A.x]*c[A.y]<c[B.x]*c[B.y];
}
void Solve(ll x){
	while(x){
		p[++tot]=x%10;
		x/=10;
	}
	num[tot+1]=1;
	v[tot+1][1]=1;
	f[tot+1][1][1]=1;
	ll flag=0,sum=1;
	for(ll i=tot;i>=1;i--){
		pos.clear();
		for(ll j=1;j<=num[i+1];j++){
			for(ll k=1;k<p[i];k++){
				if(!f[i+1][j][0]&&!f[i+1][j][1])continue;
				ll t=v[i+1][j]*k;
				if(!pos[t])v[i][pos[t]=++num[i]]=t;
				f[i][pos[t]][0]+=f[i+1][j][0]+f[i+1][j][1];
			}
		}
		if(!p[i])flag=1;
		if(!flag){
			sum*=p[i];
			if(!pos[sum])v[i][pos[sum]=++num[i]]=sum;
			f[i][pos[sum]][1]=1;
		}
		for(ll j=1;j<=num[i+1];j++){
			for(ll k=max(p[i],1ll);k<=9;k++){
				if(!f[i+1][j][0])continue;
				ll t=v[i+1][j]*k;
				if(!pos[t])v[i][pos[t]=++num[i]]=t;
				f[i][pos[t]][0]+=f[i+1][j][0];
			}
		}
		if(i!=tot){
			for(ll j=1;j<=9;j++){
				if(!pos[j])v[i][pos[j]=++num[i]]=j;
				f[i][pos[j]][0]++;
			}
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	Solve(n);pos.clear();
	for(ll j=1;j<=num[1];j++){
		if(!pos[v[1][j]])pos[v[1][j]]=++cnt;
		c[pos[v[1][j]]]+=f[1][j][0]+f[1][j][1];
	}
	sort(c+1,c+cnt+1);
	for(ll i=1;i<=cnt;i++){
		q.push((node){i,cnt});
	}
	while(m--&&q.size()){
		node t=q.top();q.pop();
		ans=(ans+c[t.x]*c[t.y]%Mod)%Mod;
		if(t.y>1)q.push((node){t.x,t.y-1});
	}
	printf("%lld",ans);
	return 0;
}