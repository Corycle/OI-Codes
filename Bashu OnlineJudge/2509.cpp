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
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
int h[N],p[N],dis[N],vis[N];
struct edge{
	int to,next,data;
}d[N*10];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
bool SPFA(int x){
	vis[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(dis[y]<dis[x]+d[i].data){
			dis[y]=dis[x]+d[i].data;
			if(vis[y])return false;
			if(!SPFA(y))return false;
		}
	}
	vis[x]=0;
	return true;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		n=read();m=read();
		int S=n+1;cnt=0;
		memset(h,0,sizeof(h));
		memset(vis,0,sizeof(vis));
		memset(dis,-0x3f,sizeof(dis));
		for(int i=1;i<=m;i++){
			int x=read(),y=read(),z=read();
			Add(x-1,y,z);//y-(x-1)==z
			Add(y,x-1,-z);
		}
		for(int i=0;i<=n;i++){
			Add(S,i,0);
		}
		dis[S]=0;
		if(SPFA(S))printf("true\n");
		else printf("false\n");
	}
	return 0;
}
