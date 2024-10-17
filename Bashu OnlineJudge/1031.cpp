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
int n,m,cnt,Root;
int a[N],h[N],f[N][2],fa[N];
struct edge{int to,next;}d[N];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void DFS(int x){
	f[x][1]=max(a[x],0);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		DFS(y);
		f[x][1]+=f[y][0];
		f[x][0]+=max(f[y][0],f[y][1]);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){int x=read();fa[x]=read();Add(fa[x],x);}
	for(int i=1;i<=n;i++)if(!fa[i])Root=i;
	DFS(Root);
	printf("%d\n",max(f[Root][0],f[Root][1]));
	return 0;
}
