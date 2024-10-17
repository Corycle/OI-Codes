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
#define fst first
#define scd second
#define mp make_pair
#define pii pair<int,ll>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
pii Ans;
vector<int>G[N];
int n,m,deg[N],Max[N],dep[N];
int BFS(int fx,int fy){
	int num=0;queue<int>q;
	for(int i=1;i<=n;i++)dep[i]=0;
	if(fx){q.push(fx);dep[fx]=1;}
	if(fy){q.push(fy);dep[fy]=1;}
	while(q.size()){
		int x=q.front();q.pop();
		Max[dep[x]]=max(Max[dep[x]],deg[x]);num=max(num,dep[x]);
		for(auto y:G[x])if(!dep[y]){dep[y]=dep[x]+1;q.push(y);}
	}
	return num;
}
pii Solve(int x,int y){
	for(int i=1;i<=n;i++)Max[i]=0;
	pii ans=mp(BFS(x,y),0);ans.scd=Max[1]-(y!=0);
	for(int i=2;i<=n;i++)if(Max[i]>1)ans.scd*=(Max[i]-1);
	if(y)ans.scd*=2;
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Ans=mp(inf,inf);
	if(n==2){puts("1 2");return 0;}
	for(int i=1;i<n;i++){int x=read(),y=read();G[x].push_back(y);G[y].push_back(x);deg[x]++;deg[y]++;}
	for(int x=1;x<=n;x++){Ans=min(Ans,Solve(x,0));for(auto y:G[x])Ans=min(Ans,Solve(x,y));}
	printf("%d %lld\n",Ans.fst,Ans.scd);
	return 0;
}
