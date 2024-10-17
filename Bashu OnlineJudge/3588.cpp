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
int n,h[1005],cnt,rd[1005],dis[1005],p[1005][13],num[1005];
struct edge{
	int to,next;
}d[1005];
void hqq_add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void init(){
	cnt=0;
	memset(h,0,sizeof(h));
	memset(d,0,sizeof(d));
	memset(p,0,sizeof(p));
	memset(rd,0,sizeof(rd));
	memset(dis,0,sizeof(dis));
	memset(num,0,sizeof(num));
}
void hqq_dfs(int x,int dep){
	int i,j,k;
	dis[x]=dep;
	for(i=h[x];i;i=d[i].next){
		int y=d[i].to;
		p[y][0]=x;
		hqq_dfs(y,dep+1);
	}
}
void lca_init(){
	int i,j,k;
	for(j=1;j<=int(log(n)/log(2));j++){
		for(i=1;i<=n;i++){
			if(p[i][j-1]!=-1)p[i][j]=p[p[i][j-1]][j-1];
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
			x=p[x][k];y=p[y][k];
		}
	}
	return p[x][0];
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	while(scanf("%d",&n)!=EOF){
		init();
		for(i=1;i<=n;i++){
			int x=read();
			k=read();
			for(j=1;j<=k;j++){
				int y=read();
				rd[y]++;
				hqq_add(x,y);
			}
		}
		int root;
		for(i=1;i<=n;i++){
			if(rd[i]==0){
				root=i;
				break;
			}
		}
		memset(p,-1,sizeof(p));
		hqq_dfs(root,1);
		lca_init();
		int m=read();
		while(m--){
			int x=read(),y=read();
			num[hqq_lca(x,y)]++;
		}
		for(i=1;i<=n;i++){
			if(num[i])printf("%d:%d\n",i,num[i]);
		}
	}
	return 0;
}