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
const int N=600005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
ll a[N],b[N],Min[N];
int fst[N],Ans1[N],Ans2[N];
int h[N],fa[N],dep[N],root[N];
struct edge{int to,next;}d[N];
struct Tree{int l,r,dis;ll data,tag1,tag2;}t[N];
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void Pushdown(int x){
	//a1(a2*x+b2)+b1=a1*a2*x+a1*b2+b1
	if(t[x].tag1!=1){
		t[x].data*=t[x].tag1;
		t[t[x].l].tag1*=t[x].tag1;
		t[t[x].l].tag2*=t[x].tag1;
		t[t[x].r].tag1*=t[x].tag1;
		t[t[x].r].tag2*=t[x].tag1;
	}
	if(t[x].tag2!=0){
		t[x].data+=t[x].tag2;
		t[t[x].l].tag2+=t[x].tag2;
		t[t[x].r].tag2+=t[x].tag2;
	}
	t[x].tag1=1;t[x].tag2=0;
}
int Merge(int x,int y){
	if(!x||!y)return x|y;
	Pushdown(x);Pushdown(y);
	if(t[x].data>t[y].data)swap(x,y);
	t[x].r=Merge(t[x].r,y);
	if(t[t[x].l].dis<t[t[x].r].dis)swap(t[x].l,t[x].r);
	t[x].dis=(t[x].r?t[t[x].r].dis+1:0);
	return x;
}
void DFS(int x,int depth){
	dep[x]=depth;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;DFS(y,depth+1);
		root[x+m]=Merge(root[x+m],root[y+m]);
	}
	while(root[x+m]){
		int fx=root[x+m];Pushdown(fx);
		if(t[root[x+m]].data<Min[x]){
			root[x+m]=Merge(t[fx].l,t[fx].r);
			if(fx<=m){Ans1[x]++;Ans2[fx]=dep[fst[fx]]-depth;}
		}
		else break;
	}
	if(a[x]==1)t[root[x+m]].tag1=b[x];//*
	if(a[x]==0)t[root[x+m]].tag2=b[x];//+
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n+m;i++)t[root[i]=i].tag1=1;
	for(int i=1;i<=n;i++){t[i+m].data=Min[i]=read();}
	for(int i=2;i<=n;i++){Add(read(),i);a[i]=read();b[i]=read();}
	for(int i=1;i<=m;i++){
		t[i].data=read();fst[i]=read();
		root[fst[i]+m]=Merge(i,root[fst[i]+m]);
	}
	DFS(1,1);
	while(root[1+m]){
		int x=root[1+m];Pushdown(x);
		if(x<=m)Ans2[x]=dep[fst[x]];
		root[1+m]=Merge(t[x].l,t[x].r);
	}
	for(int i=1;i<=n;i++)printf("%d\n",Ans1[i]);
	for(int i=1;i<=m;i++)printf("%d\n",Ans2[i]);
	return 0;
}