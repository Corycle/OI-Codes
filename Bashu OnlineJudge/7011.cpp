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
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
int h[N],a[N],sum[N],deg[N],ans[N];
struct Node{int t,pos,val;}P[N];
struct edge{int to,next;}d[N*20];
int mod(int x){return x>=Mod?x-Mod:x;}
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void Build(int x){int num=read();while(num--){int y=read();Add(x,y);deg[y]++;}}
int Pow(int x,int y){int ans=1;while(y){if(y&1)ans=1ll*ans*x%Mod;x=1ll*x*x%Mod;y>>=1;}return ans;}
void DFS(int x){
	if(sum[x]>=0)return;
	sum[x]=(P[x].t==2?P[x].val:1);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;DFS(y);
		sum[x]=1ll*sum[x]*sum[y]%Mod;
	}
}
void Solve(){
	queue<int>q;ans[0]=1;
	for(int i=0;i<=m;i++)if(!deg[i])q.push(i);
	while(q.size()){
		int x=q.front(),tmp=1;q.pop();
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(!(--deg[y]))q.push(y);
			ans[y]=mod(ans[y]+1ll*ans[x]*tmp%Mod);
			tmp=1ll*tmp*sum[y]%Mod;
		}
	}
}
int main(){
//	freopen("call.in","r",stdin);
//	freopen("call.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	m=read();
	for(int i=1;i<=m;i++){
		P[i].t=read();
		if(P[i].t==1){P[i].pos=read();P[i].val=read();}
		if(P[i].t==2)P[i].val=read();
		if(P[i].t==3)Build(i);
	}
	Build(0);
	for(int i=0;i<=m;i++)sum[i]=-1;
	for(int i=0;i<=m;i++)DFS(i);
	int tmp=sum[0];
	for(int i=1;i<=n;i++)a[i]=1ll*a[i]*tmp%Mod;
	Solve();
	for(int i=0;i<=m;i++)if(P[i].t==1)a[P[i].pos]=mod(a[P[i].pos]+1ll*P[i].val*ans[i]%Mod);
	for(int i=1;i<=n;i++)printf("%d ",a[i]);
	return 0;
}