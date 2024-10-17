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
const int N=5005;
inline int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N],c,ans;
int cd[N],fx,fy;
int n,m,flag,vis[N],pre[N];
int f[N],st;
void Add(int x,int y){
	G[x].push_back(y);
}
void DFS1(int x,int fa) {
	ans.push_back(x);
	for(int i=0;i<cd[x];i++){
		int y=G[x][i];
		if(y!=fa)DFS1(y,x);
	}
}
void Find(int x,int fa) {
	vis[x]=1;
	for(int i=0;i<cd[x];i++){
		int y=G[x][i];
		if(y==fa)continue;
		if(vis[y]&&!flag){
			st=pre[x]=y;
			f[x]=flag=1;
		}
		else if(!vis[y]){
			Find(y,x);
			if(flag&&f[y]){
				pre[x]=y;
				f[x]=1;
			}
		}
	}
	if(x==st)flag=0;
}
void DFS2(int x,int fa){
	c.push_back(x);
	for(int i=0;i<cd[x];i++){
		int y=G[x][i];
		if(y==fa)continue;
		if((x==fx&&y==fy)||(y==fx&&x==fy))continue;
		DFS2(y,x);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	for(int i=1;i<=n;i++){
		cd[i]=G[i].size();
		sort(G[i].begin(),G[i].end());
	}
	if(m==n-1)DFS1(1,0);
	else{
		flag=0;Find(1,0);int rt=st;
		for(int i=1;i<=n;i++){
			ans.push_back(inf);
		}
		do{
			fx=rt;fy=pre[rt];
			c.clear();DFS2(1,0);
			rt=pre[rt];if(ans>c)ans=c;
		}while(st!=rt);
	}
	for(int i=0;i<n;i++)printf("%d ",ans[i]);
	return 0;
}