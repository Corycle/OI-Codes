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
const int M=1<<21;
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
int a[N][N],b[N][N],f[M];
//轮廓线遍历方式：右上到左下 
//f[i]为 i 状态与最终结果之间的最优 
int DFS(int s,int flag){
	//轮廓线：横 0 竖 1 
	if(abs(f[s])<inf)return f[s];
	f[s]=flag?-inf:inf;
	int x=n+1,y=1;
	for(int i=0;i<n+m-1;i++){
		((s>>i)&1)?x--:y++;
		if(((s>>i)&3)!=1)continue;
		int nxt=s^(3<<i);
		if(flag)f[s]=max(f[s],DFS(nxt,flag^1)+a[x][y]);
		else f[s]=min(f[s],DFS(nxt,flag^1)-b[x][y]);
	}
	return f[s];
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=read();
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			b[i][j]=read();
		}
	}
	memset(f,0x3f,sizeof(f));
	f[((1<<n)-1)<<m]=0;//最终状态 
	printf("%d",DFS((1<<n)-1,1));
	return 0;
}