/*====Corycle====*/
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
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
const int Mod=1073741824;
const int N=2e5+5;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
int n,m,A,B,C,cnt,tot;
ll Ans,Fa[N],Fb[N],Fc[N];
int mu[N],vis[N],deg[N],prime[N];
struct Edge{int x,y,z;}E[N*20];
struct Node{int to,data;};
vector<Node>G[N];
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
void Prepare(int maxn){
	mu[1]=1;
	for(register int i=2;i<=maxn;i++){
		if(!vis[i]){prime[++cnt]=i;mu[i]=-1;}
		for(register int j=1;j<=cnt&&1ll*i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j])mu[i*prime[j]]=-mu[i];
			else{mu[i*prime[j]]=0;break;}
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	Prepare(1e5);
	A=read();B=read();C=read();
	int Max=max(max(A,B),C),Min=min(min(A,B),C);
	for(register int i=1;i<=A;i++)for(register int j=i;j<=A;j+=i)Fa[i]+=A/j;
	for(register int i=1;i<=B;i++)for(register int j=i;j<=B;j+=i)Fb[i]+=B/j;
	for(register int i=1;i<=C;i++)for(register int j=i;j<=C;j+=i)Fc[i]+=C/j;
	/* 1. i = j = k */
	for(register int i=1;i<=Min;i++)if(mu[i])Ans+=mu[i]*mu[i]*mu[i]*Fa[i]*Fb[i]*Fc[i];
	/* 2. i = j or i = k or j = k */
	for(register int Gcd=1;Gcd<=Max;Gcd++){
		for(register int i=1;i*Gcd<=Max;i++){
			if(!mu[i*Gcd])continue;
			for(register int j=i+1;1ll*i*j*Gcd<=Max;j++){
				if(!mu[j*Gcd])continue;
				if(gcd(i,j)==1){
					int a=i*Gcd,b=j*Gcd,Lcm=i*j*Gcd;
					int tmp1=mu[a]*mu[a]*mu[b],tmp2=mu[a]*mu[b]*mu[b];
					Ans+=tmp1*(Fa[a]*Fb[Lcm]*Fc[Lcm]+Fa[Lcm]*Fb[a]*Fc[Lcm]+Fa[Lcm]*Fb[Lcm]*Fc[a]);
					Ans+=tmp2*(Fa[b]*Fb[Lcm]*Fc[Lcm]+Fa[Lcm]*Fb[b]*Fc[Lcm]+Fa[Lcm]*Fb[Lcm]*Fc[b]);
					deg[a]++;deg[b]++;E[++tot]=(Edge){a,b,Lcm};
				}
			}
		}
	}
	/* 3. i != j and i != k and j != k */
	for(register int i=1;i<=tot;i++){
		int x=E[i].x,y=E[i].y,z=E[i].z;
		if(deg[x]<deg[y]||(deg[x]==deg[y]&&x>y))swap(x,y);
		G[x].push_back((Node){y,z});
	}
	for(register int x=1;x<=Max;x++){
		for(auto Exy:G[x])vis[Exy.to]=Exy.data;
		for(auto Exy:G[x]){
			int y=Exy.to,t1=Exy.data;
			if(!mu[y])continue;
			for(auto Eyz:G[y]){
				int z=Eyz.to;
				if(vis[z]){
					int t2=Eyz.data,t3=vis[z],Mu=mu[x]*mu[y]*mu[z];
					if(!Mu)continue;
					Ans+=Mu*(Fa[t1]*Fb[t2]*Fc[t3]+Fa[t1]*Fb[t3]*Fc[t2]+
					         Fa[t2]*Fb[t1]*Fc[t3]+Fa[t2]*Fb[t3]*Fc[t1]+
							 Fa[t3]*Fb[t1]*Fc[t2]+Fa[t3]*Fb[t2]*Fc[t1]);
				}
			}
		}
		for(auto Exy:G[x])vis[Exy.to]=0;
	}
	Ans=(Ans%Mod+Mod)%Mod;
	printf("%lld\n",Ans);
	return 0;
}