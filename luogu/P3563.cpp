/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<bitset>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#define ll long long
#define Bitset bitset<N>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=3e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
Bitset F;
ll Sum,Ans;
vector<int>G[N];
int n,Min,Root,c[N],sum[N];
void Find(int x,int fa){
	int S=0;sum[x]=1;
	for(auto y:G[x])if(y!=fa){Find(y,x);sum[x]+=sum[y];S=max(S,sum[y]);}
	S=max(S,n-sum[x]);if(S<Min){Min=S;Root=x;}
}
void DFS(int x,int fa){
	sum[x]=1;
	for(auto y:G[x])if(y!=fa){DFS(y,x);sum[x]+=sum[y];}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++){int x=read(),y=read();G[x].push_back(y);G[y].push_back(x);}
	Min=inf;Find(1,0);DFS(Root,0);
	for(int i=1;i<=n;i++)Sum+=sum[i]-1;
	for(auto x:G[Root])c[sum[x]]++;
	for(int i=1;i<=n;i++)while(c[i]>2){c[i]-=2;c[i<<1]++;}
	F[0]=1;
	for(int i=1;i<=n;i++)while(c[i]){F|=(F<<i);c[i]--;}
	for(int i=0;i<=n;i++)if(F[i])Ans=max(Ans,Sum+1ll*i*(n-i-1));
	printf("%d %lld\n",n-1,Ans);
	return 0;
}
