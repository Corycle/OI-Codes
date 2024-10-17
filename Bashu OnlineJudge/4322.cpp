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
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,L,cnt;
int h[N],a[N],f[N],id[N],pos[N],dis[N],vis[N],flag[N];
struct edge{int to,next,dist;}d[N];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
struct Node{
	int x,val;
	friend bool operator<(Node A,Node B){
		return A.val>B.val;
	}
};
priority_queue<Node>Q;
void SPFA(int sx){
	queue<int>q;q.push(sx);
	while(q.size()){
		int x=q.front();q.pop();vis[x]=0;
		for(int i=h[x];i;i=d[i].next){
			if(flag[i])continue;
			int y=d[i].to;
			if(dis[y]>dis[x]+d[i].dist){
				dis[y]=dis[x]+d[i].dist;
				if(pos[y])Q.push((Node){pos[y],dis[y]+f[pos[y]]});
				else if(!vis[y]){vis[y]=1;q.push(y);}
			}
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();L=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		Add(x,y,z);
	}
	a[1]=1;
	for(int i=1;i<=L;i++){
		id[i]=read();
		flag[id[i]]=1;
		a[i+1]=d[id[i]].to;
	}
	for(int i=2;i<=n;i++)dis[i]=inf;
	for(int i=1;i<=L+1;i++)pos[a[i]]=i;
	for(int i=L;i>=1;i--)f[i]=f[i+1]+d[id[i]].dist;
	SPFA(a[1]);
	for(int i=1;i<=L;i++){
		while(!Q.empty()&&Q.top().x<=i)Q.pop();
		if(!Q.empty())printf("%d\n",Q.top().val);
		else puts("-1");
		dis[a[i+1]]=dis[a[i]]+d[id[i]].dist;
		SPFA(a[i+1]);
	}
	return 0;
}