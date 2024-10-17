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
#define pii pair<int,int>
#define mp make_pair
#define fst first
#define scd second
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2000005;
const int M=4005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
int a[N],b[N],Ans[N];
namespace Task1{
	int f[M][M][2],g[M][M][2];
	void Main(){
		f[1][1][0]=f[1][0][1]=1;
		for(int i=2;i<=m;i++){
			for(int j=0;j<=n;j++){
				if(a[i]>=a[i-1]&&f[i-1][j-1][0]){f[i][j][0]=1;g[i][j][0]=0;}
				if(a[i]>=b[i-1]&&f[i-1][j-1][1]){f[i][j][0]=1;g[i][j][0]=1;}
				if(b[i]>=a[i-1]&&f[i-1][j][0]){f[i][j][1]=1;g[i][j][1]=0;}
				if(b[i]>=b[i-1]&&f[i-1][j][1]){f[i][j][1]=1;g[i][j][1]=1;}
			}
		}
		if(!f[m][n][0]&&!f[m][n][1])puts("-1");
		else{
			int x=m,y=f[m][n][0]?0:1,num=n;
			Ans[x]=y;
			while(x>1){
				if(y==0){y=g[x][num][y];Ans[--x]=y;num--;}
				else{y=g[x][num][y];Ans[--x]=y;}
			}
			for(int i=1;i<=m;i++){
				if(!Ans[i])printf("A");
				else printf("B");
			}
			printf("\n");
		}
	}
}
namespace Task2{
	map<int,int>vis[N],pre[N];
	struct Node{
		int x,t,num;
		friend bool operator<(Node A,Node B){
			return A.num<B.num;
		}
	};
	int id(int x,int y){return x+y*m;}
	pii pos(int x){return mp(x%m,x/m);}
	void Print(int x,int t,int num){
		if(x!=1){
			pii y=pos(pre[id(x,t)][num]);
			Print(x-1,y.scd,num-(t==0));
		}
		if(t==0)printf("A");
		else printf("B");
	}
	void Main(){
		priority_queue<Node>q;
		q.push((Node){1,0,1});
		q.push((Node){1,1,0});
		while(q.size()){
			Node x=q.top();q.pop();
			if(vis[id(x.x,x.t)][x.num])continue;
			vis[id(x.x,x.t)][x.num]=1;
			if(x.x<m){
				int now=(x.t==0?a[x.x]:b[x.x]);
				if(now<=a[x.x+1]&&!vis[id(x.x+1,0)][x.num+1]&&x.num+1<=n){
					q.push((Node){x.x+1,0,x.num+1});
					pre[id(x.x+1,0)][x.num+1]=id(x.x,x.t);
				}
				if(now<=b[x.x+1]&&!vis[id(x.x+1,1)][x.num]){
					q.push((Node){x.x+1,1,x.num});
					pre[id(x.x+1,1)][x.num]=id(x.x,x.t);
				}
			}
		}
		if(vis[id(m,0)][n]){Print(m,0,n);return;}
		if(vis[id(m,1)][n]){Print(m,1,n);return;}
		puts("-1");
	}
}
int main(){
//	freopen("building4.in","r",stdin);
//	freopen("building4.out","w",stdout);
	n=read();m=n*2;
	for(int i=1;i<=m;i++)a[i]=read();
	for(int i=1;i<=m;i++)b[i]=read();
//	Task2::Main();return 0;
	if(n<=2000)Task1::Main();
	else Task2::Main();
	return 0;
}
