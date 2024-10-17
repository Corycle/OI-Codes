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
const int Mod=998244353;
const int N=100005;
const int M=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,K;
vector<int>G[N];
int rd[N],C[M][M],S[M][M],Fac[M],F[N][M];
int mod(int x){return x>=Mod?x-Mod:x;}
void Prepare(){
	C[0][0]=1;
	for(int i=1;i<=K;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)C[i][j]=mod(C[i-1][j]+C[i-1][j-1]);
	}
	S[0][0]=1;
	for(int i=1;i<=K;i++){
		for(int j=1;j<=K;j++){
			S[i][j]=mod(S[i-1][j-1]+1ll*S[i-1][j]*j%Mod);
		}
	}
	Fac[0]=1;
	for(int i=1;i<=K;i++)Fac[i]=1ll*Fac[i-1]*i%Mod;
}
void Solve(){
	queue<int>q;
	for(int i=1;i<=n;i++){
		if(!rd[i]){q.push(i);F[i][0]=1;}
	}
	while(q.size()){
		int x=q.front();q.pop();
		for(auto y:G[x]){
			if(!(--rd[y]))q.push(y);
			F[y][0]=mod(F[y][0]+F[x][0]);
			for(int i=1;i<=K;i++){
				F[y][i]=mod(F[y][i]+mod(F[x][i-1]+F[x][i]));
			}
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();K=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		G[x].push_back(y);rd[y]++;
	}
	Prepare();
	Solve();
	for(int i=1;i<=n;i++){
		int Ans=0;
		for(int j=1;j<=K;j++){
			Ans=mod(Ans+1ll*S[K][j]*F[i][j]%Mod*Fac[j]%Mod);
		}
		printf("%d\n",Ans);
	}
	return 0;
}