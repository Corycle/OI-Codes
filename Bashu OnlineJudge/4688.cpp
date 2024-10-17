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
const int N=55,M=5005;
const int P=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char a[N][N];
int n,m,tot,cnt=1;
int f1[N][N],f2[N][N];
int id[N][N],h[M],dis[M];
struct edge{int to,next,flow;}d[P*2];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
}
bool C(char x){
	if(x=='*')return true;
	if(x=='x')return true;
	return false;
}
bool BFS(int s,int t){
	memset(dis,-1,sizeof(dis));
	queue<int>q;q.push(s);
	dis[s]=0;
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
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	int S=n*m+1,T=n*m+2;
	for(int i=1;i<=n;i++){
		scanf("%s",a[i]+1);
		for(int j=1;j<=m;j++){
			id[i][j]=++tot;
		}
	}
	tot=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(!C(a[i][j]))continue;
			if(!C(a[i][j-1])){
				tot++;
				Add(S,tot,1);
			}
			f1[i][j]=tot;
		}
	}
	for(int j=1;j<=m;j++){
		for(int i=1;i<=n;i++){
			if(!C(a[i][j]))continue;
			if(!C(a[i-1][j])){
				tot++;
				Add(tot,T,1);
			}
			f2[i][j]=tot;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]=='*'){
				Add(f1[i][j],f2[i][j],1);
			}
		}
	}
	printf("%d",Dinic(S,T));
	return 0;
}
/*
4 4
#***
*#**
**#*
xxx#
*/