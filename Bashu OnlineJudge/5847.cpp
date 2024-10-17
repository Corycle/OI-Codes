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
#include<bitset>
#define ll long long
#define pii pair<int,int>
#define fst first
#define scd second
#define mp make_pair
#define Bitset bitset<N>
using namespace std;
const int inf=0x3f3f3f3f;
const int M=5005;
const int N=205;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,vis[N];
vector<pii>G[N];
Bitset F[N],sum[M];
struct Line_Basis{
	Bitset a[N];
	void Insert(Bitset x){
		if(x.none())return;
		for(int i=n;i>=0;i--){
			if(x[i]){
				if(a[i].none()){a[i]=x;break;}
				x^=a[i];
			}
		}
	}
}P[N];
void DFS(int x){
	if(vis[x])return;vis[x]=1;
	if(G[x].empty())return;
	for(auto y:G[x])DFS(y.fst);
	for(auto y:G[x])sum[y.scd]^=F[y.fst];
	for(auto y:G[x]){P[x].Insert(sum[y.scd]);sum[y.scd].reset();}
	for(int i=0;i<=n;i++)if(P[x].a[i].none()){F[x][i]=1;break;}
}
int main(){
//	freopen("game_h.in","r",stdin);
//	freopen("game.in","r",stdin);
//	freopen("game.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),c=read();
		G[x].push_back(mp(y,c));
	}
	for(int i=1;i<=n;i++)if(!vis[i])DFS(i);
	int Q=read();Bitset Ans;Ans.reset();
	while(Q--)Ans^=F[read()];
	printf("%d",Ans.any());
	return 0;
}