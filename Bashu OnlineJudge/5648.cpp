#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
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
const int N=105;
const int M=N*N;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N][N];
int n,m,tot,cnt=1;
int a[N][N],A[N][N],B[N][N],h[M],dis[M];
struct edge{int to,next,flow;}d[M*20];
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
	int ans=0;
	if(x==t||!maxx)return maxx;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].flow&&dis[y]==dis[x]+1){
			int dlt=DFS(y,min(d[i].flow,maxx),t);
			if(!dlt)dis[y]=-1;
			d[i].flow-=dlt;
			d[i^1].flow+=dlt;
			ans+=dlt;maxx-=dlt;
			if(!maxx)return ans;
		}
	}
	return ans;
}
int Dinic(int s,int t){int ans=0;while(BFS(s,t))ans+=DFS(s,inf,t);return ans;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]+1);
		for(int j=1;j<=m;j++){
			A[i][j]=++tot;B[i][j]=++tot;
			if(s[i][j]>='0'&&s[i][j]<='9')a[i][j]=s[i][j]-'0';
		}
	}
	int ans=0,S=++tot,T=++tot;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int c=0;
			Add(A[i][j],B[i][j],inf);
			if(s[i][j]=='A'){
				Add(S,A[i][j],inf);
				for(int k=i-1;k>=1;k--)if(a[k][j]>a[c][j])c=k;
				for(int k=i-1;k>c;k--)Add(A[k][j],A[k-1][j],a[c][j]-a[k][j]);
				Add(A[i][j],A[i-1][j],a[c][j]);
				ans+=a[c][j];
			}
			if(s[i][j]=='V'){
				Add(S,A[i][j],inf);
				for(int k=i+1;k<=n;k++)if(a[k][j]>a[c][j])c=k;
				for(int k=i+1;k<c;k++)Add(A[k][j],A[k+1][j],a[c][j]-a[k][j]);
				Add(A[i][j],A[i+1][j],a[c][j]);
				ans+=a[c][j];
			}
			if(s[i][j]=='<'){
				Add(B[i][j],T,inf);
				for(int k=j-1;k>=1;k--)if(a[i][k]>a[i][c])c=k;
				for(int k=j-1;k>c;k--)Add(B[i][k-1],B[i][k],a[i][c]-a[i][k]);
				Add(B[i][j-1],B[i][j],a[i][c]);
				ans+=a[i][c];
			}
			if(s[i][j]=='>'){
				Add(B[i][j],T,inf);
				for(int k=j+1;k<=m;k++)if(a[i][k]>a[i][c])c=k;
				for(int k=j+1;k<c;k++)Add(B[i][k+1],B[i][k],a[i][c]-a[i][k]);
				Add(B[i][j+1],B[i][j],a[i][c]);
				ans+=a[i][c];
			}
		}
	}
	printf("%d",ans-Dinic(S,T));
	return 0;
}