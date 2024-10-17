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
const int Mod=20021101;
const int N=200005;
const int M=32;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,K,cnt;
int a[N],h[N],f[M],g[M],fa[N],dep[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS(int x,int depth){
	dep[x]=depth;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;DFS(y,depth+1);
	}
}
inline int mod1(int x){return x>=Mod?x-Mod:x;}
inline int mod2(int x){return x<0?x+K:x;}
int main(){
//	freopen("you.in","r",stdin);
//	freopen("you.out","w",stdout);
	n=read();K=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	for(int i=1;i<=n;i++)a[i]=read()%K;
	DFS(1,1);m=read();
	while(m--){
		int x=read(),y=read();
		memset(f,0,sizeof(f));
		f[0]=1;
		while(1){
			if(dep[x]<dep[y])swap(x,y);
			for(int i=0;i<K;i++)g[i]=mod1(f[i]+f[mod2(i-a[x])]);
			for(int i=0;i<K;i++){f[i]=g[i];g[i]=0;}
			if(x==y)break;x=fa[x];
		}
		printf("%d\n",f[0]);
	}
	return 0;
}