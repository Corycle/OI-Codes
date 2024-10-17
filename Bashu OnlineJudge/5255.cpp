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
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
int n,m,tot,Answer;
int vis[N],Ans[N],Match[N];
bool DFS(int x){
	vis[x]=tot;
	for(auto y:G[x]){
		if(!Match[y]){
			Match[Match[y]=x]=y;
			return true;
		}
	}
	random_shuffle(G[x].begin(),G[x].end());
	for(auto y:G[x]){
		int z=Match[y];
		if(vis[z]!=tot){
			Match[Match[y]=x]=y;Match[z]=0;
			if(DFS(z))return true;
			Match[Match[y]=z]=y;Match[x]=0;
		}
	}
	return false;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	srand(time(NULL));
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		G[x].push_back(y);
		G[y].push_back(x);
	}
	int DLZ=5;
	while(DLZ--){
		int tmp=0;
		for(int i=1;i<=n;i++)Match[i]=0;
		for(int i=1;i<=n;i++){
			tot++;if(!Match[i]&&DFS(i))tmp++;
		}
		if(tmp>Answer){
			Answer=tmp;
			for(int i=1;i<=n;i++)Ans[i]=Match[i];
		}
	}
	printf("%d\n",Answer);
	for(int i=1;i<=n;i++)printf("%d ",Ans[i]);
	return 0;
}