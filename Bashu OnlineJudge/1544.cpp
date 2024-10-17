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
const int N=200005;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
int n,m,k,cnt,root,ans;
int fa[N],val[N],sum[N];
struct Tree{int l,r;}t[N];
struct Edge{int s,t,data;}e[N];
inline bool cmp(Edge x,Edge y){return x.data>y.data;}
inline int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
inline void Kruskal(){
	int num=n,tot=n*2;
	sort(e+1,e+n,cmp);
	for(register int i=1;i<=tot;i++){
		fa[i]=i;sum[i]=(i<=n);
		val[i]=t[i].l=t[i].r=0;
	}
	for(register int i=1;i<n;i++){
		int x=Find(e[i].s);
		int y=Find(e[i].t);
		if(x==y)continue;
		fa[x]=fa[y]=++num;
		val[num]=e[i].data;
		t[num].l=x;t[num].r=y;
		sum[num]+=sum[t[num].l]+sum[t[num].r];
		if(num==tot-1)break;
	}
}
int top=0;
struct Stack{
	int x,Sum;
}st[N];
inline void DFS(int sx){
	st[++top]=(Stack){sx,0};
	while(top){
		int x=st[top].x;
		int Sum=st[top].Sum;
		top--;
		if(!val[x]){
			ans=max(ans,Sum);
			continue;
		}
		if(t[x].l)st[++top]=(Stack){t[x].l,Sum+sum[t[x].r]*val[x]};
		if(t[x].r)st[++top]=(Stack){t[x].r,Sum+sum[t[x].l]*val[x]};
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int T=read(),Case=0;
	while(T--){
		n=read();
		root=n+n-1;
		for(register int i=1;i<n;i++){
			e[i].s=read();
			e[i].t=read();
			e[i].data=read();
		}
		ans=0;
		Kruskal();
		DFS(root);
		printf("Case %d: %d\n",++Case,ans);
	}
	return 0;
}