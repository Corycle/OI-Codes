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
const int N=2e5+5;
const int M=63;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll dis[N];
int n,m,cnt,Size,h[N],p[N],vis[N],num[M];
struct edge{int to,next;ll dist;}d[N*2];
void Add(int x,int y,ll z){d[++cnt]=(edge){y,h[x],z};h[x]=cnt;}
struct Line_Basis{
	ll p[M],num;
	void Clear(){num=0;memset(p,0,sizeof(p));}
	void Insert(ll x){for(int i=M-1;i>=0;i--)if((x>>i)&1){if(!p[i]){p[i]=x;num++;break;}x^=p[i];}}
	void Build(){for(int i=M-1;i>=0;i--)for(int j=i-1;j>=0;j--)if((p[i]>>j)&1)p[i]^=p[j];}
}F;
int mod(int x){return x>=Mod?x-Mod:x;}
void DFS(int x,ll dist){
	vis[x]=1;dis[x]=dist;Size++;
	for(int i=0;i<M;i++)num[i]+=(dis[x]>>i)&1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(!vis[y])DFS(y,dist^d[i].dist);
		else F.Insert(dis[x]^dis[y]^d[i].dist);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();ll z=read();
		Add(x,y,z);Add(y,x,z);
	}
	int Ans=0;p[0]=1;
	for(int i=1;i<N;i++)p[i]=mod(p[i-1]<<1);
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			ll Max=0;Size=0;
			memset(num,0,sizeof(num));
			F.Clear();DFS(i,0);F.Build();
			for(int i=0;i<M;i++)Max|=F.p[i];
			for(int i=0;i<M;i++){
				if((Max>>i)&1)Ans=mod(Ans+1ll*(1ll*Size*(Size-1)/2)%Mod*p[i]%Mod*p[F.num-1]%Mod);
				else Ans=mod(Ans+1ll*num[i]*(Size-num[i])%Mod*p[i]%Mod*p[F.num]%Mod);
			}
		}
	}
	printf("%d",Ans);
	return 0;
}