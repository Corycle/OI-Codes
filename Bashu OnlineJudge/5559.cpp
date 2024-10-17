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
const ll inf=9e18;
const int N=400005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
ll f[105][55][55];
int a[N],b[N],c[N],id[N],ch[N][2];
void DFS(int x,int dfn,int depth){
	id[x]=dfn;
	if(x>n-1){
		for(int i=0;i<=depth;i++){
			for(int j=0;j<=depth;j++){
				f[id[x]][i][j]=1ll*c[x]*(a[x]+i)*(b[x]+j);
			}
		}
	}
	else{
		DFS(ch[x][0],dfn+1,depth+1);
		DFS(ch[x][1],dfn+2,depth+1);
		for(int i=0;i<=depth;i++){
			for(int j=0;j<=depth;j++){
				f[id[x]][i][j]=inf;
				f[id[x]][i][j]=min(f[id[x]][i][j],f[id[ch[x][0]]][i+1][j]+f[id[ch[x][1]]][i][j]);
				f[id[x]][i][j]=min(f[id[x]][i][j],f[id[ch[x][0]]][i][j]+f[id[ch[x][1]]][i][j+1]);
			}
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n-1;i++){
		int x=read(),y=read();
		if(x<0)x=-x+n-1;ch[i][0]=x;
		if(y<0)y=-y+n-1;ch[i][1]=y;
	}
	for(int i=n;i<=n*2-1;i++){
		a[i]=read();b[i]=read();c[i]=read();
	}
	DFS(1,1,1);
	printf("%lld",f[1][0][0]);
	return 0;
}