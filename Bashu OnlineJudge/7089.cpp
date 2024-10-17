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
const int Mod=1e9+7;
const int N=3e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
int n,m,f[N][2],g[N][2],tmp[2];
int mod(int x){return x>=Mod?x-Mod:x;}
void DFS(int x){
	int Sum=1;f[x][1]=g[x][0]=1;f[x][0]=g[x][1]=0;
	for(auto y:G[x]){
		DFS(y);
		memcpy(tmp,f[x],sizeof(tmp));
		for(int i=0;i<2;i++){
			for(int j=0;j<2;j++){
				tmp[(i+j)&1]=mod(tmp[(i+j)&1]+1ll*f[x][i]*f[y][j]%Mod);
			}
		}
		memcpy(f[x],tmp,sizeof(f[x]));
		Sum=1ll*Sum*mod(f[y][0]+1)%Mod;
		int tmp0=g[x][0],tmp1=g[x][1];
		g[x][0]=mod(g[x][0]+1ll*tmp1*f[y][1]%Mod);
		g[x][1]=mod(g[x][1]+1ll*tmp0*f[y][1]%Mod);
	}
	f[x][0]=mod(mod(f[x][0]<<1)-g[x][1]+Mod);
	f[x][1]=mod(mod(f[x][1]<<1)-Sum+Mod);
}
int main(){
//	freopen("randomdfs.in","r",stdin);
//	freopen("randomdfs.out","w",stdout);
	int Case=read();
	while(Case--){
		n=read();
		for(int i=2;i<=n;i++)G[read()].push_back(i);
		DFS(1);printf("%d\n",mod(f[1][0]+f[1][1]));
		for(int i=1;i<=n;i++)G[i].clear();
	}
	return 0;
}