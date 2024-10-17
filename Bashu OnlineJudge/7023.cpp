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
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
struct Edge{int x,y;}E[N];
bool cmp(Edge A,Edge B){return A.y<B.y;}
struct Tree{int tag,Min,Num;}Answer;
struct Segment_Tree{
	Tree t[N*4];
	void update(int p,int v){t[p].tag+=v;t[p].Min+=v;}
	void Pushdown(int p){if(t[p].tag){update(p<<1,t[p].tag);update(p<<1|1,t[p].tag);t[p].tag=0;}}
	void Pushup(int p){
		t[p].Num=0;
		t[p].Min=min(t[p<<1].Min,t[p<<1|1].Min);
		if(t[p].Min==t[p<<1].Min)t[p].Num+=t[p<<1].Num;
		if(t[p].Min==t[p<<1|1].Min)t[p].Num+=t[p<<1|1].Num;
	}
	void Build(int p,int l,int r){
		t[p]=(Tree){0,0,r-l+1};if(l==r)return;
		int mid=(l+r)>>1;Build(lson);Build(rson);
	}
	void Update(int x,int y,int v,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,v);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,v,lson);Update(x,y,v,rson);Pushup(p);
	}
	void Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){
			if(Answer.Min>t[p].Min)Answer=t[p];
			else if(Answer.Min==t[p].Min)Answer.Num+=t[p].Num;
			return;
		}
		int mid=(l+r)>>1;Pushdown(p);Query(x,y,lson);Query(x,y,rson);
	}
}tree;
int main(){
//	freopen("tree.in","r",stdin);
//	freopen("tree.out","w",stdout);
	int Case=read();
	while(Case--){
		n=read();
		for(int i=1;i<n;i++){E[i].x=read();E[i].y=read();if(E[i].x>E[i].y)swap(E[i].x,E[i].y);}
		sort(E+1,E+n,cmp);
		tree.Build(1,1,n);
		ll Ans=0;
		for(int i=1,j=1;i<=n;i++){
			tree.Update(1,i,1,1,1,n);
			while(j<n&&E[j].y==i){
				tree.Update(1,E[j].x,-1,1,1,n);
				j++;
			}
			Answer=(Tree){0,inf,0};
			tree.Query(1,i,1,1,n);
			if(Answer.Min==1)Ans+=Answer.Num;
		}
		printf("%lld\n",Ans);
	}
	return 0;
}