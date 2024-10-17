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
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n;
ll Ans;
struct Graph{
	int fa[N],sum[N];
	void Init(){for(int i=1;i<=n;i++){sum[i]=1;fa[i]=i;}}
	int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
	void Link(int x,int y){x=Find(x);y=Find(y);if(x!=y){fa[x]=y;sum[y]+=sum[x];}}
	int Sum(int x){return sum[Find(x)];}
}G[2];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();G[0].Init();G[1].Init();
	for(int i=1;i<n;i++){int x=read(),y=read(),op=read();G[op].Link(x,y);}
	for(int i=1;i<=n;i++)Ans+=1ll*G[0].Sum(i)*G[1].Sum(i);
	printf("%lld\n",Ans-n);
	return 0;
}
