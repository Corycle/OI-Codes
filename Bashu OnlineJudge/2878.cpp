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
const int N=500005;
const int M=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,S,T,cnt;
int h[N],dis[N],val[N],a[N],c[M][M];
struct edge{int to,next,flow;}d[N*2];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
}
bool BFS(int s,int t){
	memset(dis,-1,sizeof(dis));
	queue<int>q;q.push(s);dis[s]=0;
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
int Check(int x){
	int num=0;cnt=1;
	memset(h,0,sizeof(h));
	for(int i=1;i<=n;i++){
		if(val[i]>=x)continue;
		num++;
		Add(S,i,1);
		Add(i+n,T,1);
		for(int j=1;j<=n;j++){
			if(i==j||val[j]>=x)continue;
			if(c[i][j])Add(i,j+n,1);
		}
	}
	return num-Dinic(S,T);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	m=read()+1;n=read();
	S=n*2+1;T=n*2+2;
	for(int i=1;i<=n;i++){
		a[i]=val[i]=read();
		int num=read();
		for(int j=1;j<=num;j++){
			int x=read();
			c[i][x]=1;
		}
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				c[i][j]|=(c[i][k]&c[k][j]);
			}
		}
	}
	sort(a+1,a+n+1);
	int len=unique(a+1,a+n+1)-a-1;
	for(int i=1;i<=n;i++){
		val[i]=lower_bound(a+1,a+len+1,val[i])-a;
	}
	if(Check(len+1)<=m){
		printf("AK");
		return 0;
	}
	int l=1,r=len,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(Check(mid)<=m){
			ans=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	printf("%d",a[ans]);
	return 0;
}