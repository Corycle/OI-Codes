#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
int read(){
	int s=0,f=1;char sum=getchar();
	while(sum<'0'||sum>'9'){if(sum=='-')f=-1;sum=getchar();}
	while(sum>='0'&&sum<='9'){s=s*10+sum-'0';sum=getchar();}
	return s*f;
}
int n,m,cnt,ans,rt,minn,tot;
int h[N],sum[N],dis[N],vis[N];
struct edge{
	int to,next,data;
}d[N*2];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
void Find(int x,int fa,int num){//求树的重心
	sum[x]=1;
	int s=0;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa||vis[y])continue;
		Find(y,x,num);
		sum[x]+=sum[y];
		s=max(s,sum[y]);
	}
	s=max(s,num-sum[x]);
	if(s<minn){minn=s;rt=x;}
}
void dfs(int x,int fa,int dist){//x结点,父亲为fa,x到fa的距离为dist 
	dis[++tot]=dist;
	sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa||vis[y])continue;
		dfs(y,x,dist+d[i].data);
		sum[x]+=sum[y];
	}
}
int Ask(int x,int dist){//求以x为根,x到父亲距离为dist时,子树中满足条件的点对 
	int tmp=0;tot=0;
	dfs(x,0,dist);
	sort(dis+1,dis+tot+1);
	int l=1,r=tot;
	while(l<r){
		if(dis[l]+dis[r]<=m){
			tmp+=r-l;l++;
		}
		else r--;
	}
	return tmp;
}
void DFS(int x,int num){//当前子树树根，当前子树节点个数 
	minn=inf;
	Find(x,0,num);
	ans+=Ask(rt,0);
	vis[rt]=1;
	for(int i=h[rt];i;i=d[i].next){
		int y=d[i].to;
		if(vis[y])continue;
		ans-=Ask(y,d[i].data);
		DFS(y,sum[y]);
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read(),z=read();
		Add(x,y,z);Add(y,x,z);
	}
	DFS(1,n);
	printf("%d",ans);
	return 0;
}