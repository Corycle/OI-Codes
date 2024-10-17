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
const int N=10005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
/*
	走到pos，轮到x，状态t 
	t=1:必胜
	t=2:必败 
*/
int n,a[2][N],deg[2][N],f[2][N],vis[2][N];
void DFS(int pos,int x,int t){
	f[x][pos]=t;vis[x][pos]=1;
	for(int i=1;i<=a[x^1][0];i++){
		int nxt=(pos-a[x^1][i]+n)%n;
		if(!nxt)nxt=n;
		if(vis[x^1][nxt])continue;
		if(t==1){
			deg[x^1][nxt]--;
			if(!deg[x^1][nxt]){
				DFS(nxt,x^1,2);
			}
		}
		if(t==2)DFS(nxt,x^1,1);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	a[0][0]=read();for(int i=1;i<=a[0][0];i++)a[0][i]=read();
	a[1][0]=read();for(int i=1;i<=a[1][0];i++)a[1][i]=read();
	for(int i=1;i<=n;i++){
		deg[0][i]=a[0][0];f[0][i]=0;
		deg[1][i]=a[1][0];f[1][i]=0;
	}
	f[0][1]=1;vis[0][1]=1;
	f[1][1]=1;vis[1][1]=1;
	DFS(1,0,2);DFS(1,1,2);
	for(int i=2;i<=n;i++){
		if(f[0][i]==0)printf("Loop ");
		if(f[0][i]==1)printf("Win ");
		if(f[0][i]==2)printf("Lose ");
	}
	printf("\n");
	for(int i=2;i<=n;i++){
		if(f[1][i]==0)printf("Loop ");
		if(f[1][i]==1)printf("Win ");
		if(f[1][i]==2)printf("Lose ");
	}
	return 0;
}