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
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=4e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,b[N];
vector<int>G[N];
struct Node{int l,r,c;}P[N];
struct Tree{int Max,tag;};
struct Segmen_Tree{
	Tree t[N*4];
	void update(int p,int v){t[p].Max+=v;t[p].tag+=v;}
	void Pushdown(int p){if(t[p].tag){update(p<<1,t[p].tag);update(p<<1|1,t[p].tag);t[p].tag=0;}}
	void Update(int x,int y,int v,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,v);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,v,lson);Update(x,y,v,rson);
		t[p].Max=max(t[p<<1].Max,t[p<<1|1].Max);
	}
}tree[2];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		P[i].l=b[++b[0]]=read();
		P[i].r=b[++b[0]]=read();
		P[i].c=read()-1;
	}
	b[++b[0]]=0;
	sort(b+1,b+b[0]+1);b[0]=unique(b+1,b+b[0]+1)-b-1;
	for(int i=1;i<=n;i++){
		P[i].l=lower_bound(b+1,b+b[0]+1,P[i].l)-b;
		P[i].r=lower_bound(b+1,b+b[0]+1,P[i].r)-b;
		G[P[i].r].push_back(i);
	}
	for(int i=1;i<=b[0];i++){
		int M0=tree[0].t[1].Max;
		int M1=tree[1].t[1].Max;
		tree[0].Update(i,i,M1,1,1,b[0]);
		tree[1].Update(i,i,M0,1,1,b[0]);
		for(auto id:G[i])tree[P[id].c].Update(0,P[id].l,1,1,1,b[0]);
	}
	printf("%d\n",max(tree[0].t[1].Max,tree[1].t[1].Max));
	return 0;
}
