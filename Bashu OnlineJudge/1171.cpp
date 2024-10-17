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
const int N=400005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,cnt;
int h[N],d1[N],d2[N];
int f1[N],f2[N],fa[N];
struct edge{
	int to,next,data;
}d[N*2];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
void DFS(int x){
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;DFS(y);
		int dlt=f1[y]+d[i].data;
		if(f1[x]<=dlt){
			f2[x]=f1[x];d2[x]=d1[x];
			f1[x]=dlt;d1[x]=y;
		}
		else if(f2[x]<dlt){
			f2[x]=dlt;
			d2[x]=y;
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++){
		int x=read()+1,y=read()+1,z=1;
		Add(x,y,z);Add(y,x,z);
	}
	DFS(1);
	int ans=0;
	for(int i=1;i<=n;i++){
		ans=max(ans,f1[i]+f2[i]);
	}
	printf("%d",ans);
	return 0;
}
