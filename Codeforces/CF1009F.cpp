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
const int N=1000005;
inline char getch(){
    static char buf[500],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,500,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
int n,m,cnt;
int h[N],fa[N];
int tmp[N],ans[N],son[N];
int dep[N],Max[N],*f[N],*id=tmp;
struct edge{
	int to,next;
}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS1(int x,int depth){
	dep[x]=Max[x]=depth;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;
		DFS1(y,depth+1);
		if(Max[son[x]]<Max[y])son[x]=y;
	}
	Max[x]=max(Max[x],Max[son[x]]);
}
void DFS2(int x){
	f[x][0]=1;
	if(son[x]){
		f[son[x]]=f[x]+1;
		DFS2(son[x]);
		ans[x]=ans[son[x]]+1;
	}
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x]||y==son[x])continue;
		int len=Max[y]-dep[y]+1;
		f[y]=id;id+=len;DFS2(y);
		for(int j=1;j<=len;j++){
			f[x][j]+=f[y][j-1];
			if(f[x][j]>f[x][ans[x]])ans[x]=j;
			if(f[x][j]==f[x][ans[x]]&&ans[x]>j)ans[x]=j;
		}
	}
	if(f[x][ans[x]]==1)ans[x]=0;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS1(1,1);
	f[1]=id;
	id+=Max[1];
	DFS2(1);
	for(int i=1;i<=n;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}
