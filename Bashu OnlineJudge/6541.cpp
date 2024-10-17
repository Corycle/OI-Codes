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
const int Inv2=5e8+4;
const int Mod=1e9+7;
const int M=2005;
const int N=M*M;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,K,tot,cnt;
int f[N],deg[N],id[M][M],pre[N][2];
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
int mod(int x){return x>=Mod?x-Mod:x;}
int gcd(int a,int b){return b==0?a:gcd(b,a%b);}
struct Node{
	int k,b;//f[x] = k*f[x]+b = b/(1-k)
	friend Node operator+(Node A,Node B){return (Node){mod(A.k+B.k),mod(A.b+B.b)};} 
	friend Node operator-(Node A,Node B){return (Node){mod(A.k-B.k+Mod),mod(A.b-B.b+Mod)};}
	friend Node operator*(Node A,int B){return (Node){1ll*A.k*B%Mod,1ll*A.b*B%Mod};}
	friend Node operator+(Node A,int B){return (Node){A.k,mod(A.b+B)};} 
};
Node DFS1(int x,int p){
	if(x==p)return (Node){1,0};
	return (DFS1(pre[x][0],p)+f[pre[x][1]])*Inv2;
}
void DFS2(int x,int p){
	if(x==p)return;
	DFS2(pre[x][0],p);
	f[x]=1ll*mod(f[pre[x][0]]+f[pre[x][1]])*Inv2%Mod;
}
void Solve(int t){
	int len=gcd(t,K);
	for(int i=1;i<=len;i++){
		int x=id[i][t];
		Node F=(DFS1(pre[x][0],x)+f[pre[x][1]])*Inv2;
		f[x]=1ll*F.b*Pow(mod(1-F.k+Mod),Mod-2)%Mod;
		DFS2(pre[x][0],x);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();K=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)id[i][j]=++tot;
	}
	for(int i=1;i<=n;i++){
		for(int j=2;j<=n;j++){
			int x=id[i][j];
			int y=id[(i+K-1)%j+1][j];
			pre[x][0]=y;
			if(i==1)continue;
			y=id[(i+K-2)%(j-1)+1][j-1];
			pre[x][1]=y;
		}
	}
	f[id[1][1]]=1;
	for(int i=2;i<=n;i++)Solve(i);
	printf("%d",f[id[(K-1)%n+1][n]]);
	return 0;
}