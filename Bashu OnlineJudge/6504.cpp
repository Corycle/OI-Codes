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
const int Mod=1e9+7;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,K,cnt,Ans;
int vis[N],prime[N];
int mod(int x){return x>=Mod?x-Mod:x;}
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
int Phi(int x){
	int phi=x;
	for(int i=1;i<=cnt&&1ll*prime[i]*prime[i]<=x;i++){
		int p=prime[i];
		if(x%p==0){
			phi=phi/p*(p-1);
			while(x%p==0)x/=p;
		}
	}
	if(x!=1)phi=phi/x*(x-1);
	return phi;
}
void Prepare(int maxn){
	for(int i=2;i<=maxn;i++){
		if(!vis[i])prime[++cnt]=i;
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
}
struct Matrix{
	int a[4][4];
	void Init(){memset(a,0,sizeof(a));}
	friend Matrix operator*(Matrix A,Matrix B){
		Matrix C;C.Init();
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				for(int k=0;k<4;k++){
					C.a[i][j]=mod(C.a[i][j]+1ll*A.a[i][k]*B.a[k][j]%Mod);
				}
			}
		}
		return C;
	}
	friend Matrix operator^(Matrix tot,int n){
		Matrix Ans;Ans.Init();
		for(int i=0;i<4;i++)Ans.a[i][i]=1;
		while(n){
			if(n&1)Ans=Ans*tot;
			tot=tot*tot;
			n>>=1;
		}
		return Ans;
	}
};
Matrix A;
int F(int n){
	if(n==1)return 1;
	A.Init();
	A.a[0][0]=1;A.a[0][1]=0;A.a[0][2]=1;A.a[0][3]=0;
	A.a[1][0]=0;A.a[1][1]=1;A.a[1][2]=0;A.a[1][3]=1;
	A.a[2][0]=K;A.a[2][1]=0;A.a[2][2]=0;A.a[2][3]=0;
	A.a[3][0]=0;A.a[3][1]=K;A.a[3][2]=0;A.a[3][3]=0;
	A=A^(n-1);
	int Fn00=mod(A.a[0][0]+1ll*A.a[0][3]*K%Mod);
	int Fn01=mod(A.a[1][0]+1ll*A.a[1][3]*K%Mod);
	int Fn10=mod(A.a[2][0]+1ll*A.a[2][3]*K%Mod);
	return mod(Fn00+mod(Fn01+Fn10));
}
int main(){
//	freopen("bracelet.in","r",stdin);
//	freopen("bracelet.out","w",stdout);
	n=read();K=read();Prepare(1e5);
	for(int i=1;1ll*i*i<=n;i++){
		if(n%i==0){
			int a=i,b=n/i;
			Ans=mod(Ans+1ll*F(a)*Phi(b)%Mod);
			if(a!=b)Ans=mod(Ans+1ll*F(b)*Phi(a)%Mod);
		}
	}
	Ans=1ll*Ans*Pow(n,Mod-2)%Mod;
	printf("%d",Ans);
	return 0;
}