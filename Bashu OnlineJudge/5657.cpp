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
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int W,H,n,Ans,top1,top2;
struct Point{int x,y;}P[N],st1[N],st2[N];
bool cmp(Point A,Point B){return A.x<B.x;}
struct Tree{int Max,tag;};
struct Segment_Tree{
	Tree t[N*4];
	void clear(){memset(t,0,sizeof(t));}
	void update(int p,int x){t[p].Max+=x;t[p].tag+=x;}
	void Pushdown(int p){
		if(t[p].tag){
			update(p<<1,t[p].tag);
			update(p<<1|1,t[p].tag);
			t[p].tag=0;
		}
	}
	void Update(int x,int y,int val,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,val);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,val,lson);Update(x,y,val,rson);
		t[p].Max=max(t[p<<1].Max,t[p<<1|1].Max);
	}
}tree;
void Solve(){
	tree.clear();
	sort(P+1,P+n+1,cmp);
	int mid=H/2;top1=top2=0;
	for(int i=1;i<=n;i++){
		int x=P[i].x,y=P[i].y;
		int lst=i-1;
		if(y<=mid){
			while(top1&&st1[top1].y<y){
				tree.Update(st1[top1].x,lst,st1[top1].y-y,1,1,n);
				lst=st1[top1--].x-1;
			}
			if(lst!=i-1)st1[++top1]=(Point){lst+1,y};
		}
		else{
			while(top2&&st2[top2].y>y){
				tree.Update(st2[top2].x,lst,y-st2[top2].y,1,1,n);
				lst=st2[top2--].x-1;
			}
			if(lst!=i-1)st2[++top2]=(Point){lst+1,y};
		}
		st1[++top1]=(Point){i,0};
		st2[++top2]=(Point){i,H};
		tree.Update(i,i,H-x,1,1,n);
		Ans=max(Ans,(tree.t[1].Max+P[i+1].x)*2);
	}
}
int main(){
//	freopen("paint.in","r",stdin);
//	freopen("paint.out","w",stdout);
	W=read();H=read();n=read();
	for(int i=1;i<=n;i++){
		P[i].x=read();
		P[i].y=read();
	}
	P[++n]=(Point){0,0};P[++n]=(Point){0,H};
	P[++n]=(Point){W,0};P[++n]=(Point){W,H};
	Solve();
	for(int i=1;i<=n;i++)swap(P[i].x,P[i].y);
	swap(H,W);
	Solve();
	printf("%d",Ans);
	return 0;
}