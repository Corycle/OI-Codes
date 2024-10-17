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
#include<set>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,I,ans,ansA,ansB;
ll h[N],g[N],ga[N],gb[N];
ll f[25][N][2],da[25][N][2],db[25][N][2];
struct node{ll x,y;};
set<node>s;
set<node>::iterator it,lt,rt;
bool operator<(node a,node b){return a.y<b.y;}
bool cmp(ll a,ll b){
	return (abs(h[a]-h[I])<abs(h[b]-h[I]))||(abs(h[a]-h[I])==abs(h[b]-h[I])&&h[a]<h[b]);
}
void Solve(ll s,ll x0,ll &A,ll &B){
	A=B=0;
	ll t=(ll)(log(1.0*n)/log(2.0)+0.001),k=0;
	for(ll i=t;i>=0;i--){
		if(f[i][s][k]&&da[i][s][k]+db[i][s][k]<=x0){
			x0-=da[i][s][k]+db[i][s][k];
			A+=da[i][s][k];B+=db[i][s][k];
			s=f[i][s][k];
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++)h[i]=read();
	for(ll i=n;i>=1;i--){
		node p=(node){i,h[i]};
		s.insert(p);
		it=s.find(p);
		lt=rt=it;m=0;
		if(lt!=s.begin())g[++m]=(--lt)->x;
		if(lt!=s.begin())g[++m]=(--lt)->x;
		if(++rt!=s.end()){
			g[++m]=rt->x;
			if(++rt!=s.end())g[++m]=rt->x;
		}
		I=i;
		sort(g+1,g+m+1,cmp);
		if(m>=1)gb[i]=g[1];
		if(m>=2)ga[i]=g[2];
	}
	for(ll i=1;i<=n;i++){
		if(ga[i]){
			f[0][i][0]=ga[i];
			da[0][i][0]=abs(h[ga[i]]-h[i]);
		}
		if(gb[i]){
			f[0][i][1]=gb[i];
			db[0][i][1]=abs(h[gb[i]]-h[i]);
		}
	}
	ll t=(ll)(log(1.0*n)/log(2.0)+0.001);
	for(ll i=1;i<=t;i++){
		for(ll j=1;j<=n;j++){
			for(ll k=0;k<=1;k++){
				ll p=k;
				if(i==1)p=k^1;
				ll v=f[i-1][j][k];
				if(f[i-1][j][k])f[i][j][k]=f[i-1][v][p];
				if(f[i][j][k]){
					da[i][j][k]=da[i-1][j][k]+da[i-1][v][p];
					db[i][j][k]=db[i-1][j][k]+db[i-1][v][p];
				}
			}
		}
	}
	ansA=1;ansB=0;
	ll x0=read(),A,B;
	for(ll i=1;i<=n;i++){
		Solve(i,x0,A,B);
		if(!B)A=1;
		if(A*ansB<ansA*B||A*ansB==ansA*B&&h[i]>h[ans]){
			ansA=A;ansB=B;ans=i;
		}
	}
	printf("%lld\n",ans);
	m=read();
	for(ll i=1;i<=m;i++){
		ll x=read(),y=read();
		Solve(x,y,A,B);
		printf("%lld %lld\n",A,B);
	}
	return 0;
}