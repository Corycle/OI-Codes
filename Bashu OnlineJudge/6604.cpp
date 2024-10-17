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
const int Inv2=499122177;
const int Mod=998244353;
const int Phi=998244352;
const int N=4e5+5;
const int G=3;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,deg[N],fac[N],inv[N],P[N];
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
void Prepare(int maxn){
	fac[0]=fac[1]=inv[0]=inv[1]=1;P[0]=1;
	for(int i=1;i<=maxn;i++)P[i]=1ll*P[i-1]*Inv2%Mod;
	for(int i=2;i<=maxn;i++)fac[i]=1ll*fac[i-1]*i%Mod;
	for(int i=2;i<=maxn;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<=maxn;i++)inv[i]=1ll*inv[i-1]*inv[i]%Mod;
}
int C(int n,int m){return n<m?0:1ll*fac[n]*inv[m]%Mod*inv[n-m]%Mod;}
int F(int n,int m){return n<m*2?0:1ll*C(n,m*2)*C(m*2,m)%Mod*fac[m]%Mod*P[m]%Mod;}
namespace Task1{
	const int M=1005;
	int f[M][M];
	void Main(){
		f[0][n-1]=1;
		for(int x=1;x<=n;x++){
			for(int i=0;i<=deg[x]/2;i++){
				for(int j=1;j<n;j++){
					f[x][j]=mod(f[x][j]+1ll*f[x-1][j+i]*F(deg[x],i)%Mod);
				}
			}
		}
		for(int i=1;i<n;i++)printf("%d ",f[n][i]);
	}
}
namespace Task2{
	void Main(){
		for(int i=1;i<n;i++)printf("%d ",C(n-2,n-1-i));
	}
}
namespace Task3{
	int len,L,R[N],a[N],b[N];
	void Prepare(int maxn){
		len=1;L=0;while(len<=maxn){len<<=1;L++;}
		for(int i=0;i<len;i++)R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
	}
	void NTT(int a[],int n,int f){
		for(int i=0;i<n;i++)if(i<R[i])swap(a[i],a[R[i]]);
		for(int i=1;i<n;i<<=1){
			int Wn=Pow(G,Phi+f*Phi/(i<<1));
			for(int j=0;j<len;j+=(i<<1)){
				int W=1;
				for(int k=0;k<i;k++){
					int x=a[j+k],y=1ll*W*a[j+k+i]%Mod;
					a[j+k]=mod(x+y);a[j+k+i]=mod(x-y+Mod);W=1ll*W*Wn%Mod;
				}
			}
		}
		if(f==-1){
			int Inv=Pow(n,Mod-2);
			for(int i=0;i<n;i++)a[i]=1ll*a[i]*Inv%Mod;
		}
	}
	vector<int> Multi(const vector<int>&A,const vector<int>&B){
		int n=A.size(),m=B.size();Prepare(n+m-1);
		for(int i=0;i<n;i++)a[i]=A[i];
		for(int i=0;i<m;i++)b[i]=B[i];
		for(int i=n;i<len;i++)a[i]=0;
		for(int i=m;i<len;i++)b[i]=0;
		NTT(a,len,1);NTT(b,len,1);
		for(int i=0;i<len;i++)a[i]=1ll*a[i]*b[i]%Mod;
		NTT(a,len,-1);
		vector<int>C;C.resize(n+m);
		for(int i=0;i<n+m;i++)C[i]=a[i];
		return C;
	}
	vector<int> Solve(int l,int r){
		if(l==r){
			int x=l,maxn=deg[x]/2;
			vector<int>tmp;tmp.resize(maxn+1);
			for(int i=0;i<=maxn;i++)tmp[i]=F(deg[x],i);
			return tmp;
		}
		int mid=(l+r)>>1;
		return Multi(Solve(l,mid),Solve(mid+1,r));
	}
	void Main(){
		vector<int>Ans=Solve(1,n);
		for(int i=1;i<n;i++)printf("%d ",Ans[n-i-1]);
	}
}
int main(){
//	freopen("path.in","r",stdin);
//	freopen("path.out","w",stdout);
	n=read();
	int Max=0;Prepare(n);
	for(int i=1;i<n;i++){deg[read()]++;deg[read()]++;}
	for(int i=1;i<=n;i++)Max=max(Max,deg[i]);
//	if(n<=1000){Task1::Main();return 0;}
	if(Max<=2){Task2::Main();return 0;}
	Task3::Main();
	return 0;
}