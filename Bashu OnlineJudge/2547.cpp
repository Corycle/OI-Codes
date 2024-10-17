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
int n,m,len,cnt=1;
int h[N],a[N],f[N],dis[N];
struct edge{
	int to,next,flow;
}d[N*100];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
}
bool BFS(int s,int t){
	queue<int>q;
	memset(dis,-1,sizeof(dis));
	q.push(s);dis[s]=0;
	while(q.size()){
		int x=q.front();q.pop();
		if(x==t)return true;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].flow&&dis[y]==-1){
				dis[y]=dis[x]+1;
				q.push(y);
			}
		}
	}
	return false;
}
int DFS(int x,int maxx,int t){
	int ans=0,dlt=0;
	if(x==t||!maxx)return maxx;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].flow&&dis[y]==dis[x]+1){
			dlt=DFS(y,min(maxx,d[i].flow),t);
			if(!dlt)dis[y]=-1;
			d[i].flow-=dlt;
			d[i^1].flow+=dlt;
			ans+=dlt;maxx-=dlt;
			if(!maxx)return ans;
		}
	}
	return ans;
}
int Dinic(int s,int t){
	int ans=0;
	while(BFS(s,t))ans+=DFS(s,inf,t);
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++){
		for(int j=0;j<i;j++){
			if(a[j]<a[i])f[i]=max(f[i],f[j]+1);
		}
		len=max(len,f[i]);
	}
	printf("%d\n",len);
	int S=0,T=n*2+1;
	for(int i=1;i<=n;i++){
		Add(i,i+n,1);
		if(f[i]==1)Add(S,i,1);
		if(f[i]==len)Add(i+n,T,1);
		for(int j=1;j<i;j++){
			if(a[j]<a[i]&&f[i]==f[j]+1)Add(j+n,i,1);
		}
	}
	int ans=Dinic(S,T);
	printf("%d\n",ans);
	Add(S,1,inf);
	Add(1,1+n,inf);
	if(f[n]==len&&n!=1){
		Add(n+n,T,inf);
		Add(n,n+n,inf);
	}
	printf("%d\n",ans+Dinic(S,T));
	return 0;
}
