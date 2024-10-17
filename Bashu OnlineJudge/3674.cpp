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
const ll Maxn=1000000;
const ll P=1000000007;
const ll M=1000005;
const ll N=505;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,top,root,fac[M],inv[M];
ll a[N],h[N],st[N],sum[N],f[N][N];
struct Tree{ll ch[2],fa;}t[N];
ll C(ll n,ll m){
	return m>n?0:fac[n]*inv[m]%P*inv[n-m]%P;
}
void Prepare(){//预处理阶乘逆元 
	fac[0]=inv[0]=inv[1]=1;
	for(ll i=1;i<=Maxn;i++)fac[i]=fac[i-1]*i%P;
	for(ll i=2;i<=Maxn;i++)inv[i]=inv[P%i]*(P-P/i)%P;
	for(ll i=2;i<=Maxn;i++)inv[i]=inv[i-1]*inv[i]%P;
}
void DFS(ll x){
	sum[x]=f[x][0]=1;
	for(int k=0;k<2;k++){
		int y=t[x].ch[k];
		if(!y)continue;
		DFS(y);sum[x]+=sum[y];
		//每次转移先令该矩形内不放的情况用乘法原理把子树一乘
		for(ll i=min(m,sum[x]);i>=1;i--){
			for(ll j=1;j<=min(sum[y],i);j++){
				f[x][i]=(f[x][i]+f[y][j]*f[x][i-j]%P)%P;
			}
		}
	}
	//枚举该矩形放了几个 
	ll c=a[x]-a[t[x].fa];//矩阵的高 
	for(ll i=min(m,sum[x]);i>=1;i--){
		ll tmp=f[x][i];
		for(ll j=1;j<=min(i,c);j++){
			tmp=(tmp+f[x][i-j]*fac[j]%P*C(c,j)%P*C(sum[x]-i+j,j)%P)%P;
		}
		f[x][i]=tmp;
	}
}
void Build(){//建树 
	for(ll i=1;i<=n;i++){
		while(top&&a[st[top]]>a[i])top--;
		ll pre=st[top];
		t[i].fa=pre;
		t[t[pre].ch[1]].fa=i;
		t[i].ch[0]=t[pre].ch[1];
		t[pre].ch[1]=i;
		st[++top]=i;
	}
	root=t[0].ch[1];
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	Prepare();
	n=read();m=read();
	for(ll i=1;i<=n;i++)a[i]=read();
	Build();DFS(root);
	printf("%lld",f[root][m]);
	return 0;
}