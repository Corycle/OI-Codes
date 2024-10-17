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
char s[N];
int n,m,sx,sy,tx,ty;
int a[N][N],vis[N][N],dis[N][N];
int dx[8]={1,1,2,2,-1,-1,-2,-2};
int dy[8]={2,-2,1,-1,2,-2,1,-1};
struct node{int x,y;};
void BFS(){
	queue<node>q;
	q.push((node){sx,sy});
	vis[sx][sy]=1;
	while(q.size()){
		int x=q.front().x;
		int y=q.front().y;
		q.pop();
		for(int i=0;i<8;i++){
			int fx=x+dx[i],fy=y+dy[i];
			if(fx<1||fy<1||fx>n||fy>m)continue;
			if(!vis[fx][fy]){
				vis[fx][fy]=1;
				q.push((node){fx,fy});
				dis[fx][fy]=dis[x][y]+1;
			}
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	m=read();n=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=m;j++){
			a[i][j]=(s[j]=='.');
			if(s[j]=='K')sx=i,sy=j;
			if(s[j]=='H')tx=i,ty=j;
		}
	}
	BFS();
	printf("%d",dis[tx][ty]);
	return 0;
}
/*
10 11
..........
....*.....
..........
...*.*....
.......*..
..*..*...H
*.........
...*...*..
.K........
...*.....*
..*....*..
*/