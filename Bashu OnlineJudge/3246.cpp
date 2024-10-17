#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=300005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,Ans;
int h[N],fa[N],sum[N],f1[N],f2[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};h[x]=cnt;
}
void DFS(int x){
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;sum[x]++;DFS(y);
		int ans=f1[y]+f2[y]+1;
		int dlt=(f1[y]!=0)+(f2[y]!=0);
		if(sum[y]>=dlt)ans+=sum[y]-dlt;
		Ans=max(Ans,ans+1);
	}
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		int dlt=f1[y]+1;
		if(f1[y])dlt+=sum[y]-1;
		if(f1[x]<=dlt){
			f2[x]=f1[x];
			f1[x]=dlt;
		}
		else f2[x]=max(f2[x],dlt);
	}
	int ans=f1[x]+f2[x]+1;
	int dlt=(f1[x]!=0)+(f2[x]!=0);
	if(sum[x]>=dlt)ans+=sum[x]-dlt;
	Ans=max(Ans,ans);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS(1);
	printf("%d",Ans);
	return 0;
}