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
const int M=1000005;
const int N=500005;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
int n,m,S,tot;
vector<int>G[N];
vector<int>F[N];
int dep[N],dfn[M],vis[M];
int L[N],R[N],fa[N],num[N];
void DFS(int x,int depth){
	dep[x]=depth;
	dfn[++tot]=x;vis[L[x]=tot]=1;
	F[x].push_back(tot);
	for(auto y:G[x]){
		DFS(y,depth+1);dfn[++tot]=x;
		F[x].push_back(tot);
	}
	R[x]=tot;
}
int main(){
//	freopen("run.in","r",stdin);
//	freopen("run.out","w",stdout);
	int T=read();
	for(int Case=1;Case<=T;Case++){
		n=read();tot=0;
		for(int i=1;i<=n*2;i++)vis[i]=0;
		for(int i=1;i<=n;i++)fa[i]=0;
		for(int i=1;i<=n;i++){
			num[i]=read();
			G[i].clear();F[i].clear();
			for(int j=1;j<=num[i];j++){
				int x=read();fa[x]=i;
				G[i].push_back(x);
			}
		}
		int pos=0,Ans=0;
		DFS(1,1);S=read();
		while(S){
			for(auto k:F[S]){
				if(k-pos>=0&&vis[k-pos]){
					int x=dfn[k-pos];
					if(L[x]<=L[S]&&R[S]<=R[x])Ans++;
				}
			}
			S=fa[S];pos++;
		}
		printf("%d\n",Ans);
	}
	return 0;
}