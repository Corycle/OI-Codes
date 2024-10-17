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
#define pii pair<int,int>
#define mp make_pair
#define fst first
#define scd second
using namespace std;
const int inf=0x3f3f3f3f;
const int N=15005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,D,lst,type;
struct Ques{int op,v,w,e;}Q[N];
struct Node{
	int f[N];
	void Init(){f[0]=0;for(int i=1;i<=m;i++)f[i]=-inf;}
	void Update(int v,int w){for(int i=m;i>=v;i--)f[i]=max(f[i],f[i-v]+w);}
	void Query(int v){
		int ans1=0,ans2=0;
		if(f[v]>=0){ans1=1;ans2=f[v];}
		printf("%d %d\n",ans1,ans2);
		D=type*(ans1^ans2);
	}
};
struct Segment_Tree{
	vector<pii>t[N*4];
	void Update(int x,int y,int v,int w,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){t[p].push_back(mp(v,w));return;}
		int mid=(l+r)>>1;
		Update(x,y,v,w,lson);Update(x,y,v,w,rson);
	}
	void Solve(int p,int l,int r,Node F){
		for(auto x:t[p])F.Update(x.fst,x.scd);
		if(l==r){
			if(Q[l].op==1){
				Q[l].v-=D;Q[l].w-=D;Q[l].e-=D;
				Update(l+1,Q[l].e,Q[l].v,Q[l].w,1,1,n);
			}
			else F.Query(Q[l].v-D);
			return;
		}
		int mid=(l+r)>>1;
		Solve(lson,F);Solve(rson,F);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();type=read();
	for(int i=1;i<=n;i++){
		Q[i].op=read();Q[i].v=read();
		if(Q[i].op==1){Q[i].w=read();Q[i].e=read();}
	}
	Node tmp;tmp.Init();
	tree.Solve(1,1,n,tmp);
	return 0;
}