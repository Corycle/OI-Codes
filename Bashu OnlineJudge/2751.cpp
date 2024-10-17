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
const int N=10005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,maxx;
int h[N],vis[N],p[N][N>>2],pnum[N];
struct edge{
	int to,next;
}d[N*2];
void edge_add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
bool DFS(int x){
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(!vis[y]){
			vis[y]=1;
			if(pnum[y]<maxx){
				p[y][++pnum[y]]=x;
				return true;
			}
			for(int i=1;i<=pnum[y];i++){
				if(DFS(p[y][i])){
					p[y][i]=x;
					return true;
				}
			}
		}
	}
	return false;
}
bool Hungary(){
	memset(p,0,sizeof(p));
	memset(pnum,0,sizeof(pnum));
	for(int i=1;i<=m;i++){
		memset(vis,0,sizeof(vis));
		if(!DFS(i))return false;
	}
	return true;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		edge_add(i,x);
		edge_add(i,y);
	}
	int l=0,r=m,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		maxx=mid;
		if(Hungary()){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	printf("%d",ans);
	return 0;
}