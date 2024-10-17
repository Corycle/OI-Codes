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
ll G,B;
int n,m,cnt,h[N],sum[N];
struct edge{int to,next,dist;}d[N*2];
void Add(int x,int y,int z){d[++cnt]=(edge){y,h[x],z};h[x]=cnt;}
void DFS(int x,int fa){
	sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;
		DFS(y,x);sum[x]+=sum[y];
		if(sum[y]&1)G+=d[i].dist;
		B+=1ll*d[i].dist*min(sum[y],n-sum[y]);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int Case=read();
	while(Case--){
		n=read()*2;cnt=0;
		for(int i=1;i<=n;i++)h[i]=0;
		for(int i=1;i<n;i++){int x=read(),y=read(),z=read();Add(x,y,z);Add(y,x,z);}
		G=B=0;DFS(1,0);
		printf("%lld %lld\n",G,B);
	}
	return 0;
}
