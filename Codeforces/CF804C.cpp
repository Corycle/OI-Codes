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
vector<int>V[N],G[N];
int n,m,Max,ans[N],vis[N];
void DFS(int x,int fa){
	int p=1;
	for(auto c:V[x])if(ans[c])vis[ans[c]]=1;
	for(auto c:V[x])if(!ans[c]){while(vis[p])p++;ans[c]=p;vis[p]=1;}
	for(auto c:V[x])vis[ans[c]]=0;
	for(auto y:G[x])if(y!=fa)DFS(y,x);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){int k=read();while(k--)V[i].push_back(read());}
	for(int i=1;i<n;i++){int x=read(),y=read();G[x].push_back(y);G[y].push_back(x);}
	DFS(1,0);
	for(int i=1;i<=m;i++){if(!ans[i])ans[i]=1;Max=max(Max,ans[i]);}
	printf("%d\n",Max);
	for(int i=1;i<=m;i++)printf("%d ",ans[i]);
	return 0;
}
