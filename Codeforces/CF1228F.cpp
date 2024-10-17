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
const int N=132000;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Min;
vector<int>Ans,G[N];
int fa[N],num[N],sum[N],deg[N],dep[N],Max[N];
void Find(int x,int fa){
	sum[x]=1;
	for(auto y:G[x])if(y!=fa){Find(y,x);sum[x]+=sum[y];Max[x]=max(Max[x],sum[y]);}
	Max[x]=max(Max[x],n-sum[x]);Min=min(Min,Max[x]);
}
void DFS1(int x,int depth){
	sum[x]=1;dep[x]=depth;
	for(auto y:G[x])if(y!=fa[x]){fa[y]=x;DFS1(y,depth+1);sum[x]+=sum[y];}
}
void DFS2(int x){
	dep[x]++;
	for(auto y:G[x])if(y!=fa[x])DFS2(y);
}
void Solve(int x){
	if(deg[x]!=2&&deg[x]!=3)return;
	for(int i=1;i<=n;i++)dep[i]=fa[i]=sum[i]=0;
	int tot=0,fx=0;DFS1(x,1);if(deg[x]==3){tot=1;fx=x;}
	for(int i=1;i<=n;i++)if(i!=x&&(deg[i]==2||deg[i]==4)){tot++;fx=i;}
	if(tot!=1)return;tot=0;
	for(auto y:G[fx])if(y!=fa[fx]&&sum[y]!=num[dep[y]]){tot++;DFS2(y);}
	if(tot!=0&&tot!=2)return;
	int tmp=fx;while(tmp){sum[tmp]++;tmp=fa[tmp];}
	for(int i=1;i<=n;i++)if(sum[i]!=num[dep[i]])return;
	Ans.push_back(fx);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)num[i]=(1<<(n-i+1))-1;
	if(n==2){puts("2\n1 2");return 0;}n=(1<<n)-2;
	for(int i=1;i<n;i++){int x=read(),y=read();G[x].push_back(y);G[y].push_back(x);deg[x]++;deg[y]++;}
	Min=inf;Find(1,0);
	for(int i=1;i<=n;i++)if(Max[i]==Min)Solve(i);
	sort(Ans.begin(),Ans.end());
	printf("%d\n",(int)Ans.size());
	for(auto x:Ans)printf("%d ",x);
	return 0;
}
