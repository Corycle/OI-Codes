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
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,e;
int f[N];
struct node{int l,r,s;}w[N];
struct Tree{int minn;}t[N*4];
bool cmp(node x,node y){
	if(x.r!=y.r)return x.r<y.r;
	return x.l<y.l;
}
void Build(int num,int l,int r){
	t[num].minn=inf;
	if(l==r)return;
	int mid=(l+r)>>1;
	Build(lson);
	Build(rson);
}
void update(int num){
	t[num].minn=min(t[num<<1].minn,t[num<<1|1].minn);
}
void Change(int x,int y,int num,int l,int r){
	if(x<l||x>r)return;
	if(l==r){
		t[num].minn=y;
		return;
	}
	int mid=(l+r)>>1;
	Change(x,y,lson);
	Change(x,y,rson);
	update(num);
}
int Ask(int x,int y,int num,int l,int r){
	if(y<l||x>r)return inf;
	if(x<=l&&r<=y)return t[num].minn;
	int mid=(l+r)>>1;
	return min(Ask(x,y,lson),Ask(x,y,rson));
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();e=read();
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=n;i++){
		w[i].l=max(read(),m);
		w[i].r=min(read(),e);
		w[i].s=read();
	}
	sort(w+1,w+n+1,cmp);
	Build(1,m,e);
	Change(m,f[m]=0,1,m,e);
	for(int i=1;i<=n;i++){
		int c=Ask(max(w[i].l-1,m),w[i].r,1,m,e)+w[i].s;
		if(f[w[i].r]>c)Change(w[i].r,f[w[i].r]=c,1,m,e);
	}
	if(f[e]!=inf)printf("%d",f[e]);
	else printf("-1");
	return 0;
}