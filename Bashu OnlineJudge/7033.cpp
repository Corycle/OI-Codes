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
const int N=2005;
const int M=N*N*4;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N][N];
int dx[8]={1,0,-1,0,1,1,-1,-1};
int dy[8]={0,1,0,-1,1,-1,1,-1};
int n,m,tot,top,Ans,b[N][N],vis[N][N],dis[N][N];
struct Node{
	int x,y;
	int Dist(){return max(abs(x),abs(y));}
	friend Node operator+(Node A,Node B){return (Node){A.x+B.x,A.y+B.y};}
	friend Node operator-(Node A,Node B){return (Node){A.x-B.x,A.y-B.y};}
	friend int operator*(Node A,Node B){return A.x*B.x+A.y*B.y;}
	friend int operator^(Node A,Node B){return A.x*B.y-A.y*B.x;}
}P[M],A[M];
int Cross(Node A,Node B,Node C){return (A-C)^(B-C);}
bool cmp(Node A,Node B){int tmp=Cross(A,B,P[1]);return tmp?tmp>0:(P[1]-A).Dist()<(P[1]-B).Dist();}
void BFS(int sx,int sy){
	queue<Node>q;q.push((Node){sx,sy});vis[sx][sy]=1;
	while(q.size()){
		int x=q.front().x,y=q.front().y;q.pop();
		for(int i=0;i<8;i++){
			int fx=x+dx[i],fy=y+dy[i];
			if(fx<1||fx>n||fy<1||fy>m||vis[fx][fy]||s[fx][fy]=='X')continue;
			vis[fx][fy]=1;dis[fx][fy]=dis[x][y]+1;q.push((Node){fx,fy});
		}
	}
}
int main(){
//	freopen("forest.in","r",stdin);
//	freopen("forest.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]+1);
		for(int j=1;j<=m;j++){
			if(s[i][j]=='*')P[++tot]=(Node){i,j};
			if(s[i][j]=='X'){
				if(s[i+1][j]!='X')P[++tot]=(Node){i+1,j};
				if(s[i-1][j]!='X')P[++tot]=(Node){i-1,j};
				if(s[i][j+1]!='X')P[++tot]=(Node){i,j+1};
				if(s[i][j-1]!='X')P[++tot]=(Node){i,j-1};
			}
		}
	}
	int Minx=inf,Miny=inf,id=0;
	for(int i=1;i<=tot;i++){
		if(P[i].y<Miny||(P[i].y==Miny&&P[i].x<Minx)){Minx=P[i].x;Miny=P[i].y;id=i;}
	}
	swap(P[1],P[id]);
	sort(P+2,P+tot+1,cmp);
	A[++top]=P[1];A[++top]=P[2];
	for(int i=3;i<=tot;i++){
		while(top>1&&Cross(P[i],A[top],A[top-1])>=0)top--;
		A[++top]=P[i];
	}
	A[top+1]=P[1];
	for(int i=1;i<=top;i++){Ans+=(A[i+1]-A[i]).Dist();b[A[i].x][A[i].y]=1;}
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(s[i][j]=='*')BFS(i,j);
	for(int i=1;i<=top;i++){
		if((A[i+1]-A[i]).Dist()==dis[A[i].x][A[i].y]+dis[A[i+1].x][A[i+1].y]){
			printf("%d\n",Ans);return 0;
		}
	}
	int tmp=inf;
	for(int i=1;i<=top;i++){
		tmp=min(tmp,dis[A[i].x][A[i].y]+dis[A[i+1].x][A[i+1].y]-(A[i+1]-A[i]).Dist());
	}
	printf("%d\n",Ans+tmp);
	return 0;
}