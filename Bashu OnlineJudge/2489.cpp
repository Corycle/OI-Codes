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
#include<set>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,tot,a[N],b[N],h[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
namespace Task1{
	const int M=3005;
	int f[M][M];
	void DFS(int x,int fa){
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(y==fa)continue;DFS(y,x);
			for(int j=1;j<=tot;j++)f[x][j]+=f[y][j];
		}
		for(int i=1;i<=tot;i++)f[x][i]+=(a[x]!=i);
		for(int i=tot-1;i>=1;i--)f[x][i]=min(f[x][i],f[x][i+1]);
	}
	void Main(){DFS(1,0);printf("%d\n",f[1][1]);}
}
namespace Task2{
	#define set_it multiset<int>::iterator
	multiset<int>F[N];
	void Merge(int x,int y){
		if(F[x].size()<F[y].size())swap(F[x],F[y]);
		for(auto tmp:F[y])F[x].insert(tmp);F[y].clear();
	}
	void DFS(int x,int fa){
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(y==fa)continue;
			DFS(y,x);Merge(x,y);
		}
		set_it p=F[x].lower_bound(a[x]);
		if(p!=F[x].begin())F[x].erase(--p);
		F[x].insert(a[x]);
	}
	void Main(){DFS(1,0);printf("%d\n",n-(int)F[1].size());}
}
int main(){
//	freopen("weight.in","r",stdin);
//	freopen("weight.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=b[i]=read();
	sort(b+1,b+n+1);tot=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+tot+1,a[i])-b;
	for(int i=1;i<n;i++){int x=read(),y=read();Add(x,y);Add(y,x);}
//	if(n<=3000){Task1::Main();return 0;}
	Task2::Main();
	return 0;
}