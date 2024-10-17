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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,cnt,tot,Cnt,Num,Belong;
int h[N],b[N],P[N],sum[N],num[N],Sum[N],deg[N],dfn[N],low[N],flag[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
int mod(int x){return x>=Mod?x-Mod:x;}
void Tarjan(int x,int pre){
	dfn[x]=low[x]=++tot;flag[x]=1;
	b[x]=Belong;sum[x]=(s[x]-'0');
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(i==(pre^1))continue;
		if(!dfn[y]){
			Tarjan(y,i);sum[x]+=sum[y];
			low[x]=min(low[x],low[y]);
			if(dfn[x]<=low[y]){
				flag[x]&=((sum[y]&1)==0);
				num[x]++;Sum[x]+=sum[y];
			}
		}
		else low[x]=min(low[x],dfn[y]);
	}
	if(!pre)num[x]--;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();P[0]=1;
	for(int i=1;i<N;i++)P[i]=mod(P[i-1]<<1);
	while(T--){
		n=read();m=read();cnt=1;Num=Cnt=0;
		for(int i=1;i<=n;i++)dfn[i]=low[i]=sum[i]=b[i]=0;
		for(int i=1;i<=n;i++)deg[i]=num[i]=Sum[i]=h[i]=0;
		for(int i=1;i<=m;i++){
			int x=read(),y=read();
			Add(x,y);Add(y,x);
			deg[x]++;deg[y]++;
		}
		scanf("%s",s+1);
		for(int i=1;i<=n;i++){
			if(!dfn[i]){
				Belong=i;Num++;
				Tarjan(i,0);
				Cnt+=(sum[i]&1);
			}
		}
		int Ans=m-n+Num;
		printf("%d ",Cnt?0:P[Ans]);
		for(int i=1;i<=n;i++){
			if(!deg[i])printf("%d ",(Cnt-sum[i])?0:P[Ans]);
			else{
				if(!flag[i]||((sum[b[i]]-(s[i]-'0')-Sum[i])&1)||(Cnt-(sum[b[i]]&1)))printf("0 ");
				else printf("%d ",P[Ans-deg[i]+num[i]+1]);
			}
		}
		puts("");
	}
	return 0;
}