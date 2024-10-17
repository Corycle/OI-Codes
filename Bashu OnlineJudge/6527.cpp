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
const int N=1e7+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int cnt;
int vis[N],prime[N];
ll f[N],g[N],Ans[N];
void Prepare(int maxn){
	f[1]=1;
	for(int i=2;i<=maxn;i++){
		if(!vis[i]){prime[++cnt]=i;f[i]=i+1;g[i]=i;}
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]){
				g[i*prime[j]]=prime[j];
				f[i*prime[j]]=f[i]*f[prime[j]];
			}
			else{
				g[i*prime[j]]=g[i]*prime[j];
				if(i*prime[j]==g[i*prime[j]])f[i*prime[j]]=f[i]*prime[j]+1;
				else f[i*prime[j]]=f[i/g[i]]*f[g[i]*prime[j]];
				break;
			}
		}
	}
	for(int i=2;i<=maxn;i++)Ans[i]=Ans[i-1]+i-1-f[i]+i;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();Prepare(1e7);
	while(T--)printf("%lld\n",Ans[read()]);
	return 0;
}