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
const int Maxn=1e7;
const int M=1e7+5;
const int N=5e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
bool vis[M];
int n,m,cnt,Ans;
int a[N],p[N],c[M],f[M],s[M],mu[M],prime[M/10];
int mod(int x){return x>=Mod?x-Mod:x;}
void Prepare(int maxn){
	mu[1]=1;
	for(int i=2;i<=maxn;i++){
		if(!vis[i]){prime[++cnt]=i;mu[i]=-1;}
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j])mu[i*prime[j]]=-mu[i];
			else{mu[i*prime[j]]=0;break;}
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Prepare(Maxn);
	for(int i=1;i<=n;i++)c[a[i]=read()]++;
	p[0]=1;for(int i=1;i<=n;i++)p[i]=mod(p[i-1]<<1);
	for(int j=1;j<=cnt;j++)for(int i=Maxn/prime[j];i>=1;i--)c[i]+=c[i*prime[j]];
	for(int i=1;i<=Maxn;i++)f[i]=mu[i]*c[i];
	for(int j=1;j<=cnt;j++)for(int i=1;1ll*i*prime[j]<=Maxn;i++)f[i*prime[j]]+=f[i];
	for(int i=1;i<=Maxn;i++)s[i]=mod(p[c[i]]-1+Mod);
	for(int j=cnt;j>=1;j--)for(int i=1;1ll*i*prime[j]<=Maxn;i++)s[i]=mod(s[i]-s[i*prime[j]]+Mod);
	for(int i=2;i<=Maxn;i++)Ans=mod(Ans+1ll*f[i]*s[i]%Mod);
	printf("%d",Ans);
	return 0;
}
