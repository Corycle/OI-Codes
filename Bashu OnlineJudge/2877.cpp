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
const int N=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,ans;
int a[N][N],vis[N];
void DFS(int x,int depth){
	vis[x]=1;
	if(depth==n+1){
		ans++;
		vis[x]=0;
		return;
	}
	for(int i=1;i<=n;i++){
		if(a[x][i]&&!vis[i])DFS(i,depth+1);
	}
	vis[x]=0;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			a[i][j]=read();
		}
	}
	for(int i=1;i<=n;i++)DFS(i,2);
	printf("%d",ans);
	return 0;
}