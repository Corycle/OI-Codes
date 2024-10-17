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
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
bool flag;
int n,m,cnt,tmp,Max,Min,Root;
int h[N],deg[N],sum[N],num[N],dep[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void Find(int x,int fa){
	int Max=0;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;
		Find(y,x);
		sum[x]+=sum[y];
		Max=max(Max,sum[y]);
	}
	Max=max(Max,n-sum[x]);
	if(Max<Min){Min=Max;Root=x;}
}
void DFS(int x,int fa,int depth){
	dep[x]=depth;
	if(num[depth]==-1)num[depth]=deg[x];
	if(num[depth]!=deg[x])flag=false;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;
		DFS(y,x,depth+1);
	}
}
bool Check(int x){for(int i=1;i<=n;i++)num[i]=-1;flag=true;DFS(x,0,1);return flag;}
int Line(int x,int fa){
	if(deg[x]>2)return 0;
	if(deg[x]==1){tmp=x;return 1;}
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;
		int len=Line(y,x);
		return len?len+1:0;
	}
	return 0;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++){int x=read(),y=read();Add(x,y);Add(y,x);deg[x]++;deg[y]++;}
	Min=inf;Find(1,0);
	if(Check(Root)){printf("%d\n",Root);return 0;}
	int fx=0,flen=0;
	for(int i=h[Root];i;i=d[i].next){
		int x=d[i].to,len=Line(x,Root);
		if(!len)continue;
		if(fx&&len!=flen){if(Check(tmp)){printf("%d\n",tmp);return 0;}break;}
		if(!fx){fx=tmp;flen=len;if(Check(tmp)){printf("%d\n",tmp);return 0;}}
	}
	puts("-1");
	return 0;
}
