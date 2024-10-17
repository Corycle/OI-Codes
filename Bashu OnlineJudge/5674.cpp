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
const int N=2000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,K,cnt;
int h[N],dis[N],vis[N];
struct edge{int to,next,data;}d[N];
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
			if(vis[y]){vis[x]=0;return false;}
			if(!SPFA(y)){vis[x]=0;return false;}
		}
	}
	vis[x]=0;
	return true;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		n=read();m=read();K=read();cnt=0;
		for(int i=1;i<=n+m;i++)h[i]=dis[i]=vis[i]=0;
		while(K--){
			int x=read(),y=read(),z=read();
			Add(x,y+n,z);Add(y+n,x,-z);
		}
		int flag=0;
		for(int i=1;i<=n+m;i++){
			dis[i]=0;
			if(!SPFA(i)){flag=1;break;}
		}
		if(flag)puts("No");
		else puts("Yes");
	}
	return 0;
}