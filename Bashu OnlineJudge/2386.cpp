#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=400005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,q,cnt,num;
int h[N],a[N],fa[N],vis[N],ans[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
int Find(int x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
void Link(int x){
	if(vis[x])return;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(vis[y])continue;
		int fx=Find(x),fy=Find(y);
		if(fx!=fy){
			fa[fx]=fy;
			num--;
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	q=read();num=n;
	for(int i=1;i<=q;i++){
		a[i]=read();
		vis[a[i]]=1;
	}
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=n;i++)Link(i);
	for(int i=q;i>=1;i--){
		vis[a[i]]=0;
		ans[i]=num-i;
		Link(a[i]);
	}
	ans[0]=num;
	for(int i=0;i<=q;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}