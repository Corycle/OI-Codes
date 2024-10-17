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
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
int n,m,cnt,tot,a[N],h[N],rk[N],vis[N],num[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
bool MCS(){
	int Max=0;tot=0;
	for(int i=0;i<=n;i++){G[i].clear();vis[i]=0;}
	for(int i=1;i<=n;i++)G[num[i]=0].push_back(i);
	for(int t=n;t>=1;t--){
		while(num[G[Max].back()]==-1){G[Max].pop_back();while(G[Max].empty())Max--;}
		a[t]=G[Max].back();int x=a[t];num[x]=-1;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(num[y]!=-1){G[++num[y]].push_back(y);Max=max(Max,num[y]);}
		}
	}
	for(int i=1;i<=n;i++)rk[a[i]]=i;
	for(int t=n;t>=1;t--){
		int x=a[t],fx=0;
		if(!h[x])continue;
		for(int i=h[x];i;i=d[i].next){int y=d[i].to;if(rk[y]>=rk[x]&&(!fx||rk[y]<rk[fx]))fx=y;}
		vis[fx]=++tot;
		for(int i=h[fx];i;i=d[i].next){int y=d[i].to;if(rk[y]>=rk[fx])vis[y]=tot;}
		for(int i=h[x];i;i=d[i].next){int y=d[i].to;if(rk[y]>=rk[x]&&vis[y]!=tot)return 0;}
	}
	return 1;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();cnt=0;
	for(int i=1;i<=n;i++)h[i]=0;
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	puts(MCS()?"Perfect":"Imperfect");
	return 0;
}