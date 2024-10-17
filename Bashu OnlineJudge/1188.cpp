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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans[N];
int n,m,tot,cnt=1;
int h[N],dfn[N],low[N],sum1[N],sum2[N];
struct edge{int to,next;}d[N*10];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void Tarjan(int x,int pre){
	dfn[x]=low[x]=++tot;
	sum1[x]=1;sum2[x]=n-1;Ans[x]=(n-1)*2;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(i==(pre^1))continue;
		if(!dfn[y]){
			Tarjan(y,i);
			sum1[x]+=sum1[y];
			low[x]=min(low[x],low[y]);
			if(low[y]>=dfn[x]){
				sum2[x]-=sum1[y];
				Ans[x]+=1ll*sum1[y]*(n-sum1[y]-1);
			}
		}
		else low[x]=min(low[x],dfn[y]);
	}
	Ans[x]+=1ll*sum2[x]*(n-sum2[x]-1);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	Tarjan(1,0);
	for(int i=1;i<=n;i++)printf("%lld\n",Ans[i]);
	return 0;
}