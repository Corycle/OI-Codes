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
const int Phi=998244352;
const int N=525000;
const int G=3;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>F[N];
int m,n,K,Ans,len,L,R[N],a[N],f[N],t1[N],t2[N],fac[N],inv[N];
struct cmp{
	bool operator()(int x,int y){return a[x]>a[y];}
};
priority_queue<int,vector<int>,cmp>q;
int mod(int x){return x>=Mod?x-Mod:x;}
int Pow(int x,int y){
	int ans=1;
	while(y){if(y&1)ans=1ll*ans*x%Mod;x=1ll*x*x%Mod;y>>=1;}
	return ans;
}
void Init(){
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(int i=2;i<N;i++)fac[i]=1ll*fac[i-1]*i%Mod;
	for(int i=2;i<N;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<N;i++)inv[i]=1ll*inv[i-1]*inv[i]%Mod;
}
int C(int n,int m){return n<m?0:1ll*fac[n]*inv[m]%Mod*inv[n-m]%Mod;}
void Get(int id,int num){
	F[id].resize(num);q.push(id);
	for(int i=0;i<num;i++)F[id][i]=1ll*C(num,i)*fac[num-1]%Mod*inv[num-i-1]%Mod;
}
void Prepare(int maxn){
	len=1;L=0;while(len<=maxn){len<<=1;L++;}
	for(int i=0;i<len;i++)R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
}
void NTT(int a[],int n,int f){
	for(int i=0;i<n;i++)if(i<R[i])swap(a[i],a[R[i]]);
	for(int i=1;i<n;i<<=1){
		int Wn=Pow(G,Phi+f*Phi/(i<<1));
		for(int j=0;j<n;j+=(i<<1)){
			int W=1;
			for(int k=0;k<i;k++){
				int x=a[j+k],y=1ll*W*a[j+k+i]%Mod;
				a[j+k+i]=mod(x-y+Mod);
				a[j+k]=mod(x+y);
				W=1ll*W*Wn%Mod;
			}
		}
	}
	if(f==-1){
		int Inv=Pow(n,Mod-2);
		for(int i=0;i<n;i++)a[i]=1ll*a[i]*Inv%Mod;
	}
}
vector<int> Multi(const vector<int>&A,const vector<int>&B){
	int n=A.size(),m=B.size();Prepare(n+m-2);
	for(int i=0;i<n;i++)t1[i]=A[i];
	for(int i=0;i<m;i++)t2[i]=B[i];
	for(int i=n;i<len;i++)t1[i]=0;
	for(int i=m;i<len;i++)t2[i]=0;
	NTT(t1,len,1);NTT(t2,len,1);
	for(int i=0;i<len;i++)t1[i]=1ll*t1[i]*t2[i]%Mod;
	NTT(t1,len,-1);
	vector<int>C;C.resize(n+m-1);
	for(int i=0;i<n+m-1;i++)C[i]=t1[i];
	return C;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	m=read();n=read();K=read();Init();int Inv=1;
	for(int i=1;i<=m;i++){a[i]=read();Get(i,a[i]);}
	for(int i=1;i<=m;i++)Inv=1ll*Inv*inv[a[i]]%Mod;
	while(q.size()>1){
		int x=q.top();q.pop();
		int y=q.top();q.pop();
		F[x]=Multi(F[x],F[y]);
		a[x]+=a[y];q.push(x);
		F[y].clear();
	}
	int x=q.top();
	int num=F[x].size();
	for(int i=0;i<num;i++)f[i]=1ll*F[x][i]*fac[n-i]%Mod;
	for(int i=K;i<num;i++)Ans=mod(Ans+1ll*((i-K)&1?Mod-1:1)*C(i,K)%Mod*f[i]%Mod);
	Ans=1ll*Ans*Inv%Mod;
	printf("%d",Ans);
	return 0;
}