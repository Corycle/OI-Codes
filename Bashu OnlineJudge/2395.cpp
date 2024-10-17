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
int n,m,cnt,total,S,T;
int g[N][N],dis[N],Gap[N],h[N];
struct edge{
	int to,next,data;
}d[N*N];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
int DFS(int x,int maxx){
	int ans=0,dlt=0;
	if(x==T)return maxx;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].data&&dis[x]==dis[y]+1){
			dlt=DFS(y,min(maxx,d[i].data));
			d[i].data-=dlt;
			d[i^1].data+=dlt;
			ans+=dlt;maxx-=dlt;
			if(dis[S]==n||!maxx)return ans;
		}
	}
	if(!(--Gap[dis[x]]))dis[S]=total;
	Gap[++dis[x]]++;
	return ans;
}
int SAP(){
	memset(dis,0,sizeof(dis));
	memset(Gap,0,sizeof(Gap));
	Gap[0]=total;
	int ans=0;
	while(dis[S]<total)ans+=DFS(S,inf);
	return ans;
}
void Build(int maxx){
	cnt=1;
	memset(h,0,sizeof(h));
	for(int i=1;i<=n;i++){
		Add(S,i,maxx);
		Add(i,S,0);
		Add(i,i+n,m);
		Add(i+n,i,0);
		
		Add(i+n*2,i+n*3,m);
		Add(i+n*3,i+n*2,0);
		Add(i+n*3,T,maxx);
		Add(T,i+n*3,0);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(g[i][j]){
				Add(i,j+n*3,1);
				Add(j+n*3,i,0);
			}
			else{
				Add(i+n,j+n*2,1);
				Add(j+n*2,i+n,0);
			}
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	S=0;T=n*4+1;
	total=n*4+2;
	for(int i=1;i<=n;i++){
		char s[N];
		scanf("%s",s+1);
		for(int j=1;j<=n;j++){
			g[i][j]=s[j]=='Y'?1:0;
		}
	}
	int l=0,r=n,ans;
	while(l<=r){
		int mid=(l+r)>>1;
		Build(mid);
		if(SAP()==mid*n){
			ans=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	printf("%d",ans);
	return 0;
}