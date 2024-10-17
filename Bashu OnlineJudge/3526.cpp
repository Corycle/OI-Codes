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
#define ctz __builtin_ctz
#define clz __builtin_clz
using namespace std;
const int inf=0x3f3f3f3f;
const int Mod=998244353;
const int N=1e6+5;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Q;
int lowbit(int x){return x&(-x);}
int mod(int x){return x>=Mod?x-Mod:x;}
struct Node{
	int val[M],tag,Sum;
	void Init(){memset(val,0,sizeof(val));tag=Sum=0;}
	friend Node operator*(Node A,Node B){
		Node C;C.Init();
		int SumA=A.Sum,SumB=B.Sum;
		for(int i=0;i<M;i++){
			SumA=mod(SumA+1ll*(1<<i)*A.val[i]%Mod);
			SumB=mod(SumB+1ll*(1<<i)*B.val[i]%Mod);
		}
		int Sum=0;
		for(int i=M-1;i>=0;i--){
			SumA=mod(SumA-1ll*(1<<i)*A.val[i]%Mod+Mod);
			SumB=mod(SumB-1ll*(1<<i)*B.val[i]%Mod+Mod);
			C.val[i]=mod(Sum+mod(1ll*SumA*B.val[i]%Mod+1ll*SumB*A.val[i]%Mod));
			Sum=mod(Sum+1ll*(1<<i)*A.val[i]%Mod*B.val[i]%Mod);
		}
		C.Sum=mod(Sum+1ll*A.Sum*B.Sum%Mod);
		C.tag=A.tag^B.tag;
		return C;
	}
	int Query(int p){return p==tag?Sum:val[31-clz(p^tag)];}
}a[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Q=read();
	for(int i=1;i<=n;i++){
		int x=read(),v=read();a[i].tag=x;
		while(x){a[i].val[ctz(x)]=1ll*x*(x^v)%Mod;x-=lowbit(x);}
	}
	for(int i=2;i<=n;i++)a[i]=a[i-1]*a[i];
	while(Q--){int x=read(),p=read();printf("%d\n",a[x].Query(p));}
	return 0;
}