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
ll Ans,Num,f[N];
int n,m,cnt,a[N],h[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void DFS(int x,int fa,int op){
	f[x]=a[x];
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;if(y==fa)continue;
		DFS(y,x,op);f[x]+=max(f[y],0ll);
	}
	if(op)Ans=max(Ans,f[x]);
	else if(Ans==f[x]){Num++;f[x]=-inf;}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Ans=-inf;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){int x=read(),y=read();Add(x,y);Add(y,x);}
	DFS(1,0,1);DFS(1,0,0);
	printf("%lld %lld\n",Ans*Num,Num);
	return 0;
}
