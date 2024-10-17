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
const int Mod=10007;
const int N=100005;
const int M=19;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int cnt,mu[N],vis[N],prime[N];
int C[N][M],F[N][M],Pow[N][M],sum[N][M][12];
int mod(int x){return x>=Mod?x-Mod:x;}
void Prepare(){
	mu[1]=1;
	for(int i=2;i<N;i++){
		if(!vis[i]){prime[++cnt]=i;mu[i]=-1;}
		for(int j=1;j<=cnt&&1ll*i*prime[j]<N;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j])mu[i*prime[j]]=-mu[i];
			else{mu[i*prime[j]]=0;break;}
		}
		mu[i]=mod(mu[i]+Mod);
	}
	for(int i=0;i<N;i++){
		C[i][0]=Pow[i][0]=1;
		for(int j=1;j<=i&&j<M;j++){
			C[i][j]=mod(C[i-1][j-1]+C[i-1][j]);
		}
	}
	for(int T=1;T<N;T++){
		for(int i=1;i<=11;i++){
			Pow[T][i]=1ll*Pow[T][i-1]*T%Mod;
		}
	}
	for(int c=0;c<M;c++){
		for(int d=1;d<N;d++){
			if(!mu[d])continue;
			for(int T=d;T<N;T+=d)F[T][c]=F[T][c]+mu[d]*C[T/d-1][c];
		}
	}
	for(int i=1;i<N;i++){
		for(int j=0;j<M;j++){
			F[i][j]%=Mod;
			for(int k=0;k<=11;k++)sum[i][j][k]=(sum[i-1][j][k]+F[i][j]*Pow[i][k])%Mod;
		}
	}
}
int n,c,m[M];
struct Node{
	int a[12],num;
	void Init(int x){memset(a,0,sizeof(a));a[0]=x;num=0;}
	void Multi(int A,int B){//\sum_{i=0}^{n}{a[i] x^i} * (Ax+B)
		Node C;C.Init(0);num++;
		for(int i=0;i<=num;i++)C.a[i]=a[i]*B%Mod;
		for(int i=0;i<num;i++)C.a[i+1]=mod(C.a[i+1]+a[i]*A%Mod);
		for(int i=0;i<=num;i++)a[i]=C.a[i];
	}
}node;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	Prepare();
	int Case=read();
	while(Case--){
		n=read();c=read();
		for(int i=1;i<=n;i++)m[i]=read();
		sort(m+1,m+n+1);
		int Min=m[1],Ans=0;
		for(int l=1,r=0;l<=Min;l=r+1){
			node.Init(1);r=inf;
			for(int i=1;i<=n;i++){
				int t=m[i]/l;r=min(r,m[i]/t);
				node.Multi(Mod-1ll*(1+t)*t/2%Mod,1ll*m[i]*t%Mod);
			}
			for(int i=0;i<=n;i++){
				Ans=mod(Ans+node.a[i]*mod(sum[r][c-2][i]-sum[l-1][c-2][i]+Mod)%Mod);
			}
		}
		printf("%lld\n",Ans);
	}
	return 0;
}