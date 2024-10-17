#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
using namespace std;
//struct _{};
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int read(){ 
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,h[20005],cnt,p[20005][25],dis[20005],vis[20005],a[5],ans,ans2,dis2[20005];
struct edge{
	int to,next,data;
}d[40005];
void hqq_add(int x,int y,int z){
	cnt++;
	d[cnt].to=y;
	d[cnt].next=h[x];
	d[cnt].data=z;
	h[x]=cnt;
}
void tree(int x){
	int i,j,k;
	vis[x]=1;
	for(i=h[x];i;i=d[i].next){
		if(vis[d[i].to]==0){
			dis[d[i].to]=dis[x]+1;
			dis2[d[i].to]=dis2[x]+d[i].data;
			p[d[i].to][0]=x;
			tree(d[i].to);
		}
	}
}
int hqq_lca(int x,int y){
	int i,j,k;
	if(dis[x]<dis[y])swap(x,y);
	k=int(log(dis[x])/log(2));
	for(k;k>=0;k--){
		if(dis[x]-(1<<k)>=dis[y])x=p[x][k];
	}
	if(x==y)return x;
	k=int(log(dis[x])/log(2));
	for(k;k>=0;k--){
		if(p[x][k]!=p[y][k]){
			x=p[x][k];
			y=p[y][k];
		}
	}
	return p[x][0];
}
void solve(int x,int y,int z){
	int i,j=0,k;
	k=hqq_lca(x,y);
	j=dis2[x]+dis2[y]-2*dis2[k];
	j+=dis2[z]+dis2[k]-2*dis2[hqq_lca(k,z)];
	if(ans>j){
		ans=j;
		ans2=k;
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();
	a[1]=read();a[2]=read();a[3]=read();
	memset(p,-1,sizeof(p));
	for(i=1;i<n;i++){
		j=read();k=read();
		int l=read();
		hqq_add(j,k,l);
		hqq_add(k,j,l);
	}
	tree(1);
	for(j=1;j<=int(log(n)/log(2));j++){
		for(i=1;i<=n;i++){
			if(p[i][j-1]!=-1)p[i][j]=p[p[i][j-1]][j-1];
		}
	}
	ans=0x3f3f3f3f;
	solve(a[1],a[2],a[3]);
	solve(a[1],a[3],a[2]);
	solve(a[2],a[3],a[1]);
	printf("%d\n%d",ans2,ans);
	return 0;
}