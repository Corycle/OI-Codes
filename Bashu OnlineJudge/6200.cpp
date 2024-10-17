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
const int N=234;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,K,tot,Max,Ans1,Ans2;
int a[N],b[N],c[N],d[N],vis[N],f[N][N],id[N][N];
bool Belong(int x,int y){return (x|y)==y;}
struct Node{int x,y;};
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
queue<Node>q;
void SPFA(int S){
	while(q.size()){
		int x=q.front().x,y=q.front().y;
		q.pop();vis[id[x][y]]=0;
		for(int i=0;i<4;i++){
			int fx=x+dx[i],fy=y+dy[i];
			if(fx<1||fx>n||fy<1||fy>m||a[id[fx][fy]]==-1)continue;
			if(f[id[fx][fy]][S]>f[id[x][y]][S]+d[id[fx][fy]]){
				f[id[fx][fy]][S]=f[id[x][y]][S]+d[id[fx][fy]];
				if(!vis[id[fx][fy]]){q.push((Node){fx,fy});vis[id[fx][fy]]=1;}
			}
		}
	}
}
int Steiner_Tree(int mid){
	for(int S=0;S<(1<<K);S++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				int x=id[i][j];
				if(a[x]==-1||!Belong(1<<c[a[x]],S))continue;
				for(int T=S;T;T=(T-1)&S){
					f[x][S]=min(f[x][S],f[x][T]+f[x][S^T]-d[x]);
				}
				if(f[x][S]!=inf){q.push((Node){i,j});vis[id[i][j]]=1;}
			}
		}
		SPFA(S);
	}
	int Ans=inf;
	for(int i=1;i<=tot;i++)Ans=min(Ans,f[i][(1<<K)-1]);
	return Ans;
}
void Prepare(int x){
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=tot;i++){
		if(a[i]==-1)continue;
		d[i]=N+(b[i]>x);
		f[i][1<<c[a[i]]]=d[i];
	}
}
bool Check(int x){
	Prepare(x);
	int Ans=Steiner_Tree(x),num=Ans/N;
	if(!x)return Ans!=inf&&num<=Ans1;
	else return num-(Ans%N)>=(num+1)/2;
}
void Solve(){
	for(int i=0;i<=Max;i++)c[i]=rand()%K;
	if(!Check(0))return;
	int l=1,r=1e9,Ans=inf;
	while(l<=r){
		int mid=(l+r)>>1;
		if(Check(mid)){
			Ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	int dlt=Ans;
	Ans=Steiner_Tree(Ans);
	int num=Ans/N;Ans=Ans%N;
	if(num<Ans1||(num==Ans1&&dlt<Ans2)){
		Ans1=num;Ans2=dlt;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int Case=read();
	srand(time(NULL));
	while(Case--){
		n=read();m=read();K=read();
		Ans1=Ans2=inf;Max=-1;tot=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++)id[i][j]=++tot;
		}
		for(int i=1;i<=tot;i++)a[i]=read();
		for(int i=1;i<=tot;i++)b[i]=read();
		for(int i=1;i<=tot;i++)Max=max(Max,a[i]);
		int T=N;while(T--)Solve();
		if(Ans1==inf)printf("-1 -1\n");
		else printf("%d %d\n",Ans1,Ans2);
	}
	return 0;
}