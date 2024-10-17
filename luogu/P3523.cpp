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
const int N=3e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
int n,m,Lim,Ans,a[N],f[N],g[N];
void DFS(int x,int fa){
	f[x]=inf;g[x]=-inf;
	for(auto y:G[x]){
		if(y==fa)continue;
		DFS(y,x);
		f[x]=min(f[x],f[y]+1);
		g[x]=max(g[x],g[y]+1);
	}
	if(a[x]&&f[x]>Lim)g[x]=max(g[x],0);
	if(f[x]+g[x]<=Lim)g[x]=-inf;
	if(g[x]==Lim){Ans++;f[x]=0;g[x]=-inf;}
}
bool Check(int x){Lim=x;Ans=0;DFS(1,0);return Ans+(g[1]>=0)<=m;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){int x=read(),y=read();G[x].push_back(y);G[y].push_back(x);}
	int l=0,r=n,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(Check(mid)){ans=mid;r=mid-1;}
		else l=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}
