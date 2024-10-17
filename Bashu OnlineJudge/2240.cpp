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
const ll Mod=65521;
const ll N=100;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll K,n,cnt,tot;
map<ll,ll>Hash;
ll Sum[N]={1,1,1,3,16,125};//n^(n-2)
ll b[N],p[N],fa[N],sum[N],num[N][N];
ll Find(ll x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
void Merge(ll x,ll y){
	fa[Find(x)]=Find(y);
}
struct Matrix{
	ll n,m,a[N][N];
	void Clean(){
		n=m=0;
		memset(a,0,sizeof(a));
	}
}F,G;
Matrix Multi(Matrix A,Matrix B){
	Matrix C;C.Clean();
	C.n=A.n;C.m=B.m;
	for(ll i=1;i<=C.n;i++){
		for(ll j=1;j<=C.m;j++){
			for(ll k=1;k<=A.m;k++){
				C.a[i][j]=(C.a[i][j]+A.a[i][k]*B.a[k][j]%Mod)%Mod;
			}
		}
	}
	return C;
}
Matrix Pow(Matrix A,Matrix B,ll y){
	Matrix ans=A,tot=B;
	while(y){
		if(y&1)ans=Multi(ans,tot);
		tot=Multi(tot,tot);
		y>>=1;
	}
	return ans;
}
void DFS(ll x){//最小表示法找连通情况 
	if(x==K+1){
		memset(sum,0,sizeof(sum));
		ll tmp=0;cnt++;
		for(ll i=1;i<=K;i++){
			sum[b[i]]++;
			tmp+=b[i]*p[i-1];
			num[cnt][i]=b[i];
		}
		F.a[1][cnt]=1;
		for(ll i=1;i<=tot;i++){
			F.a[1][cnt]*=Sum[sum[i]];//Sum预处理出来 
		}
		Hash[tmp]=cnt;
		return;
	}
	for(ll i=1;i<=tot;i++){b[x]=i;DFS(x+1);b[x]=0;}
	if(x!=1){tot++;b[x]=tot;DFS(x+1);tot--;b[x]=0;}
}
ll Get_Sta(){
	ll sta=0,scc=1,vis[N];
	memset(vis,0,sizeof(vis));
	for(ll i=2;i<=K+1;i++){
		if(!vis[i]){
			vis[i]=1;
			sta+=scc*p[i-2];
			for(ll j=i+1;j<=K+1;j++){
				if(Find(i)==Find(j)){
					vis[j]=1;
					sta+=scc*p[j-2];
				}
			}
			scc++;
		}
	}
	return Hash[sta];
}
void Update(ll sta,ll addv){
	for(ll i=1;i<=K+1;i++)fa[i]=i;
	for(ll i=1;i<=K;i++){
		for(ll j=i+1;j<=K;j++){
			if(num[sta][i]==num[sta][j])Merge(i,j);
		}
	}
	for(int i=1;i<=K;i++){
		if((addv>>(i-1))&1){
			ll fx=Find(i),fy=Find(K+1);
			if(fx==fy)return;fa[fx]=fy;
		}
	}
	for(ll i=2;i<=K+1;i++){
		if(Find(i)==Find(1)){
			G.a[sta][Get_Sta()]++;
			break;
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	p[0]=1;for(ll i=1;i<=7;i++)p[i]=p[i-1]*7%Mod;
	K=read();n=read();
	ll maxn=1<<K;tot=1;DFS(1);
	for(ll i=1;i<=cnt;i++){
		for(ll j=0;j<maxn;j++)Update(i,j);
	}
	F.n=1;F.m=cnt;
	G.n=cnt;G.m=cnt;
	Matrix ans=Pow(F,G,n-K);
	printf("%lld",ans.a[1][1]);
	return 0;
}