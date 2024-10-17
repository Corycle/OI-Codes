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
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
struct Ques{int n,m,a,id;}P[N];
int cnt,mu[N],vis[N],Ans[N],prime[N];
bool cmp(Ques A,Ques B){return A.a<B.a;}
int Sum(int x){return (1ll*x*(x+1)/2)%Mod;}
int mod(int x){return x>=Mod?x-Mod:x;}
int Sqr(int x){return 1ll*x*x%Mod;}
struct BIT{
	int c[N];
	int lowbit(int x){return x&(-x);}
	void Add(int x,int y){for(;x<N;x+=lowbit(x))c[x]=mod(c[x]+y);}
	int Ask(int x){int ans=0;for(;x>=1;x-=lowbit(x))ans=mod(ans+c[x]);return ans;}
	int Query(int l,int r){return mod(Ask(r)-Ask(l-1)+Mod);}
}tree;
void Prepare(){
	mu[1]=1;
	for(int i=2;i<N;i++){
		if(!vis[i]){prime[++cnt]=i;mu[i]=-1;}
		for(int j=1;j<=cnt&&1ll*i*prime[j]<N;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j])mu[i*prime[j]]=-mu[i];
			else{mu[i*prime[j]]=0;break;}
		}
	}
	for(int i=1;i<N;i++)mu[i]=mod(mu[i]+Mod);
}
inline void Update(int x){
	for(int i=x;i<N;i+=x)tree.Add(i,1ll*x*Sqr(i/x)%Mod*mu[i/x]%Mod);
}
int main(){
//	freopen("gcdlcm.in","r",stdin);
//	freopen("gcdlcm.out","w",stdout);
	int T=read();Prepare();
	for(int i=1;i<=T;i++){
		P[i].n=read();P[i].m=read();
		P[i].a=read();P[i].id=i;
	}
	int pos=0;
	sort(P+1,P+T+1,cmp);
	for(int t=1;t<=T;t++){
		while(pos<P[t].a)Update(++pos);
		int n=P[t].n,m=P[t].m;
		int maxn=min(n,m),ans=0;
		for(int i=1,j=0;i<=maxn;i=j+1){
			j=min(n/(n/i),m/(m/i));
			ans=mod(ans+1ll*Sum(n/i)*Sum(m/i)%Mod*tree.Query(i,j)%Mod);
		}
		Ans[P[t].id]=ans;
	}
	for(int i=1;i<=T;i++)printf("%d\n",Ans[i]);
	return 0;
}