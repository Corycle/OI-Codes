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
const int N=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,S,T,cnt=1;
int h[N],a[N],b[N];
int dis[N],Gap[N],sum[N],num[N],lst[N];
struct edge{
	int to,next,data;
}d[N*N];
void edge_add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
int DFS(int x,int maxx){
	int ans=0;
	if(x==T)return maxx;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].data&&dis[x]==dis[y]+1){
			int dlt=DFS(y,min(maxx,d[i].data));
			d[i].data-=dlt;
			d[i^1].data+=dlt;
			ans+=dlt;maxx-=dlt;
			if(dis[S]==n||!maxx)return ans;
		}
	}
	if(!(--Gap[dis[x]]))dis[S]=n;
	Gap[++dis[x]]++;
	return ans;
}
int SAP(){
	Gap[0]=n;
	int ans=0;
	while(dis[S]<n)ans+=DFS(S,inf);
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	m=read();n=read();
	S=0;T=n+1;
	for(int i=1;i<=m;i++)a[i]=read();
	for(int i=1;i<=n;i++){
		num[i]=read();
		for(int j=1;j<=num[i];j++){
			int x=read();
			if(!lst[x]){
				edge_add(S,i,a[x]);
				edge_add(i,S,0);
			}
			else{
				edge_add(lst[x],i,inf);
				edge_add(i,lst[x],0);
			}
			lst[x]=i;
		}
		b[i]=read();
		edge_add(i,T,b[i]);
		edge_add(T,i,0);
	}
	n+=2;
	printf("%d",SAP());
	return 0;
}