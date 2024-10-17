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
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
int a[N][N],vis[N],cd[N],ans[N];
void DFS(int x,int depth){
	if(depth==m+2){
		for(int i=1;i<=m;i++)printf("%d->",ans[i]);
		printf("%d",ans[m+1]);
		exit(0);
	}
	for(int i=1;i<=n;i++){
		if(a[x][i]){
			a[x][i]=a[i][x]=0;
			ans[depth]=i;
			DFS(i,depth+1);
			a[x][i]=a[i][x]=1;
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	if(n==1){
		printf("1");
		return 0;
	}
	int s=0,num=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			a[i][j]=read();
			if(a[i][j]){
				m++;
				cd[i]++;
			}
		}
	}
	m/=2;
	for(int i=n;i>=1;i--){
		if(cd[i]&1){
			s=i;num++;
		}
	}
	if(num==0)s=1;
	if(num==0||num==2){
		ans[1]=s;
		DFS(s,2);
	}
	printf("No Solution！");
	return 0;
}