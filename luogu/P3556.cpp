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
#define fst first
#define scd second
#define mp make_pair
#define pii pair<int,int>
using namespace std;
const int inf=0x3f3f3f3f;
const int M=1e6+5;
const int N=5005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
struct Node{int x,d,id;};
int n,m,cnt,vis[N][2],dis[N][2],Ans[M];
vector<Node>Q[N];
vector<int>G[N];
void BFS(int sx){
	memset(vis,0,sizeof(vis));
	memset(dis,0x3f,sizeof(dis));
	queue<pii>q;q.push(mp(sx,0));
	vis[sx][0]=1;dis[sx][0]=0;
	while(q.size()){
		int x=q.front().fst,p=q.front().scd;q.pop();
		for(auto y:G[x]){
			if(vis[y][p^1])continue;
			dis[y][p^1]=dis[x][p]+1;
			q.push(mp(y,p^1));
			vis[y][p^1]=1;
		}
	}
	for(auto tmp:Q[sx])Ans[tmp.id]|=(dis[tmp.x][tmp.d&1]<=tmp.d);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();int Case=read();
	for(int i=1;i<=m;i++){int x=read(),y=read();G[x].push_back(y);G[y].push_back(x);}
	for(int i=1;i<=Case;i++){
		int x=read(),y=read(),z=read();
		Q[x].push_back((Node){y,z,i});
		Q[y].push_back((Node){x,z,i});
		if(x==y&&G[x].size()==0&&z)Ans[i]=2;
	}
	for(int i=1;i<=n;i++)BFS(i);
	for(int i=1;i<=Case;i++)puts(Ans[i]==1?"TAK":"NIE");
	return 0;
}
