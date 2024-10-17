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
const int M=1e6+5;
const int N=1e3+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
int n,m,T,Ans,s[N][N],vis[N][N];
struct Node{int x,y;};
queue<Node>q;
vector<Node>G[M];
void BFS(Node S){
	q.push(S);vis[S.x][S.y]=1;
	while(q.size()){
		Node t=q.front();Ans++;q.pop();
		for(int i=0;i<4;i++){
			int x=t.x+dx[i],y=t.y+dy[i];
			if(x<1||x>n||y<1||y>m||vis[x][y])continue;
			vis[x][y]=1;
			if(s[x][y]==s[t.x][t.y])q.push((Node){x,y});
			else G[s[x][y]].push_back((Node){x,y});
		}
	}
}
int main(){
//	freopen("color.in","r",stdin);
//	freopen("color.out","w",stdout);
	n=read(),m=read(),T=read(),read();
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)s[i][j]=read();
	BFS((Node){1,1});
	while(T--){
		int x=read();
		for(auto t:G[x])BFS(t);G[x].clear();
		cout<<Ans<<'\n';
	}
	return 0;
}