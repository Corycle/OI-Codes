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
int n,m,cnt;
int h[N],rd[N],vis[N],dis1[N],dis2[N];
struct edge{int to,next,dist;}d[N*10];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
struct Node{int x,dist;};
bool operator<(Node x,Node y){
	return x.dist>y.dist;
}
void Dijkstra(){
	memset(dis1,0x3f,sizeof(dis1));dis1[1]=0;
	priority_queue<Node>q;q.push((Node){1,0});
	while(q.size()){
		int x=q.top().x;q.pop();
		if(vis[x])continue;vis[x]=1;
		int Dist=max(dis1[x],dis2[x]);
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].dist==-1){
				dis2[y]=max(dis2[y],Dist);
				if(!(--rd[y]))q.push((Node){y,max(dis1[y],dis2[y])});
			}
			else{
				if(dis1[y]>Dist+d[i].dist){
					dis1[y]=Dist+d[i].dist;
					if(!rd[y])q.push((Node){y,max(dis1[y],dis2[y])});
				}
			}
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		if(x!=y)Add(x,y,z);
	}
	for(int i=1;i<=n;i++){
		rd[i]=read();
		for(int j=1;j<=rd[i];j++){
			Add(read(),i,-1);
		}
	}
	Dijkstra();
	printf("%d",max(dis1[n],dis2[n]));
	return 0;
}