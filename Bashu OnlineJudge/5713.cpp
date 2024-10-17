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
#include<unordered_map>
#define ll long long
#define fst first
#define scd second
using namespace std;
const int inf=0x3f3f3f3f;
const int N=205;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,Mod,cnt;
int fac[N],inv[N],vis[N];
int C[N][N],f[N][N][N],prime[N];
vector<int>Num;
unordered_map<int,int>F[N],G[N];
int gcd(int x,int y){return !y?x:gcd(y,x%y);}
int lcm(int x,int y){return x/gcd(x,y)*y;}
int mod(int x){return x>=Mod?x-Mod:x;}
int Sqr(int x){return 1ll*x*x%Mod;}
void Prepare(){
	prime[0]=1;
	memset(f,-1,sizeof(f));
	for(int i=2;i<=n;i++){
		if(!vis[i])prime[++cnt]=i;
		for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
	for(int i=0;i<=n;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++){
			C[i][j]=mod(C[i-1][j-1]+C[i-1][j]);
		}
	}
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(int i=2;i<=n;i++)fac[i]=1ll*fac[i-1]*i%Mod;
	for(int i=2;i<=n;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<=n;i++)inv[i]=1ll*inv[i-1]*inv[i]%Mod;
}
void DFS(int x,int d){
	if(prime[d]*prime[d]>n)return;
	while(1){
		DFS(x,d+1);
		x*=prime[d];
		if(x>n)break;
		Num.push_back(x);
	}
}
int Calc(int n,int num,int x){
	if(f[n][num][x]!=-1)return f[n][num][x];
	int ans=inv[num];
	for(int i=1;i<=num;i++){
		ans=1ll*ans*C[n-(i-1)*x][x]%Mod*fac[x-1]%Mod;
	}
	return f[n][num][x]=ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Mod=read();Prepare();
	Num.push_back(1);DFS(1,1);F[0][1]=1;
	for(int t=0;t<=cnt;t++){
		int p=prime[t];
		if(p*p<=n&&p!=1)continue;
		for(int i=0;i<=n;i++)G[i].clear();
		G[0][1]=1;
		for(auto tmp:Num){
			int x=tmp*p;
			for(int j=n;j>=1;j--){
				for(int i=1;i*x<=j;i++){
					for(auto k:G[j-i*x]){
						int y=lcm(k.fst,tmp);
						G[j][y]=mod(G[j][y]+1ll*k.scd*Calc(j,i,x)%Mod);
					}
				}
			}
		}
		for(int i=n;i>=1;i--){
			for(int j=1;j<=i;j++){
				for(auto A:G[j]){
					for(auto B:F[i-j]){
						int x=lcm(A.fst,B.fst);
						F[i][x]=mod(F[i][x]+1ll*A.scd*B.scd%Mod*Sqr(p)%Mod*C[i][j]%Mod);
					}
				}
			}
		}
	}
	int Ans=0;
	for(auto ans:F[n])Ans=mod(Ans+1ll*Sqr(ans.fst)*ans.scd%Mod);
	Ans=1ll*Ans*inv[n]%Mod;
	printf("%d",Ans);
	return 0;
}