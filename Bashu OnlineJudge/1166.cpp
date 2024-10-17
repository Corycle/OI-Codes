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
const int N=200005;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
struct Graph{
	int cnt,h[N];
	struct edge{
		int from,to,next,data;
	}d[N];
	void Add(int x,int y,int z){
		d[++cnt]=(edge){x,y,h[x],z};
		h[x]=cnt;
	}
	void Init(){
		cnt=1;
		memset(h,0,sizeof(h));
	}
}G1,G2;
int n,m,tot,top,Ans;
int q[N],v[N],dep[N],dfn[N],low[N],flag[N];
int pre[N],fa[N],f1[N],f2[N],st[N],f[N][2];
void Tarjan(int x){
	dfn[x]=low[x]=++tot;
	for(int i=G1.h[x];i;i=G1.d[i].next){
		int y=G1.d[i].to,w=G1.d[i].data;
		if(i==(pre[x]^1))continue;
		if(!dfn[y]){
			st[++top]=i;
			pre[y]=i;Tarjan(y);
			low[x]=min(low[x],low[y]);
			if(dfn[x]<low[y]){//树边 
				top--;
				G2.Add(x,y,w);
				G2.Add(y,x,w);
			}
			if(dfn[x]==low[y]){//回来了是个环 
				int sum=0,num=0;
				while(1){
					int j=st[top--];
					v[++num]=G1.d[j].from;
					sum+=G1.d[j].data;
					f1[G1.d[j].from]=sum;
					if(G1.d[j].from==x&&G1.d[j].to==y)break;
				}
				flag[++n]=1;
				for(int j=1;j<=num;j++){
					int fx=v[j];
					f2[fx]=sum-f1[fx];
					G2.Add(n,fx,min(f1[fx],f2[fx]));
					G2.Add(fx,n,min(f1[fx],f2[fx]));
				}
			}
		}
		else if(dfn[x]>dfn[y]){
			st[++top]=i;
			low[x]=min(low[x],dfn[y]);
		}
	}
}
void DFS(int x,int depth){
	int num=0;
	dep[x]=depth;
	for(int i=G2.h[x];i;i=G2.d[i].next){
		int y=G2.d[i].to,w=G2.d[i].data;
		if(y==fa[x])continue;
		fa[y]=x;DFS(y,depth+1);
		int dlt=f[y][0]+w;
		if(f[x][0]<dlt){
			f[x][1]=f[x][0];
			f[x][0]=dlt;
		}
		else f[x][1]=max(f[x][1],dlt);
	}
	if(flag[x]){
		int l=1,r=0;
		for(int i=G2.h[x];i;i=G2.d[i].next){
			v[++num]=G2.d[i].to;//整个环放进去 
		}
		for(int i=1;i<=num;i++)v[num+i]=v[i];
		for(int i=1;i<=num;i++)swap(v[i],v[num*2-i+1]);
		for(int i=1;i<=num*2;i++){
			while(l<=r&&i-q[l]>num/2)l++;
			if(l<=r)Ans=max(Ans,f[v[i]][0]+f[v[q[l]]][0]+i-q[l]);
			while(l<r&&f[v[q[r]]][0]-q[r]<f[v[i]][0]-i)r--;
			q[++r]=i;
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	G1.Init();G2.Init();
	n=read();
	int T=read();
	while(T--){
		int num=read(),x=read();
		for(int i=2;i<=num;i++){
			int y=read();
			G1.Add(x,y,1);
			G1.Add(y,x,1);
			x=y;
		}
	}
	Tarjan(1);DFS(1,1);
	for(int i=1;i<=n;i++){
		if(!flag[i])Ans=max(Ans,f[i][0]+f[i][1]);
	}
	printf("%d",Ans);
	return 0;
}