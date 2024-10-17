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
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
int h[N],top[N],dep[N],son[N];
int p[N][30],maxbit[N],Max[N],len[N];
vector<int>s1[N],s2[N];
struct edge{
	int to,next;
}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS1(int x,int depth){
	dep[x]=Max[x]=depth;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(dep[y])continue;
		DFS1(y,depth+1);
		p[y][0]=x;
		if(Max[y]>Max[son[x]])son[x]=y;
	}
	Max[x]=max(Max[x],Max[son[x]]);
}
void DFS2(int x,int tp){
	top[x]=tp;len[x]=1;
	if(son[x]){
		DFS2(son[x],tp);
		len[x]+=len[son[x]];
	}
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==p[x][0]||y==son[x])continue;
		DFS2(y,y);
	}
}
void ST(){
	int k=(int)(log(n)/log(2));
	for(int j=1;j<=k;j++){
		for(int i=1;i<=n;i++){
			if(p[i][j-1]!=-1){
				p[i][j]=p[p[i][j-1]][j-1];
			}
		}
	}
}
void Find(int x){
	int rt=x;
	for(int i=1;i<=len[rt]&&x>0;i++){
		s1[rt].push_back(x);
		x=p[x][0];
	}
	x=rt;
	for(int i=1;i<=len[rt]&&x>0;i++){
		s2[rt].push_back(x);
		x=son[x];
	}
}
int Ask(int x,int k){
	if(k>dep[x])return 0;
	if(!k)return x;
	x=p[x][maxbit[k]];
	k-=(1<<maxbit[k]);
	int tp=top[x];
	int dis=dep[x]-dep[tp];
	if(k>dis)return s1[tp][k-dis];
	if(k<dis)return s2[tp][dis-k];
	if(k==dis)return tp;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	memset(p,-1,sizeof(p));
	n=read();m=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS1(1,1);
	DFS2(1,1);
	for(int i=1;i<=n;i++){
		if(i==top[i])Find(i);
		if(i>1)maxbit[i]=maxbit[i>>1]+1;
	}
	ST();
	int ans=0;
	while(m--){
		int x=read()^ans;
		int y=read()^ans;
		ans=Ask(x,y);
		printf("%d\n",ans);
	}
	return 0;
}