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
#define fst first
#define scd second
#define mp make_pair
#define pii pair<int,int>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1.5e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Q,qnt,tot;
struct Node{int x,y,s,t;}a[N],P[N],Ans[N];
struct Tree{int l,r,Max;};
struct Segment_Tree{
	#define lson t[p].l,l,mid
	#define rson t[p].r,mid+1,r
	Tree t[N*20];
	int tot,Root;
	void Clear(){tot=Root=0;}
	int NewNode(){tot++;t[tot]=(Tree){0,0,0};return tot;}
	void Update(int x,int y,int val,int &p,int l,int r){
		if(!p)p=NewNode();
		if(x<=l&&r<=y){t[p].Max=max(t[p].Max,val);return;}
		int mid=(l+r)>>1;
		if(x<=mid)Update(x,y,val,lson);
		if(y>mid)Update(x,y,val,rson);
	}
	int Query(int x,int p,int l,int r){
		if(x<l||x>r||!p)return 0;
		if(l==r)return t[p].Max;
		int mid=(l+r)>>1;
		return max(t[p].Max,max(Query(x,lson),Query(x,rson)));
	}
	#undef lson
	#undef rson
}Tx,Ty;
struct _Segment_Tree{
	#define lson p<<1,l,mid
	#define rson p<<1|1,mid+1,r
	vector<int>t[N*4];
	vector<pii>tmp[2];
	void update(int op,int L){
		if(op==0){int pos=Ty.Query(L,Ty.Root,0,n);tmp[0].push_back(mp(L,pos));Tx.Update(pos,n-L-1,L+1,Tx.Root,0,n);}
		if(op==1){int pos=Tx.Query(L,Tx.Root,0,n);tmp[1].push_back(mp(L,pos));Ty.Update(pos,n-L-1,L+1,Ty.Root,0,n);}
	}
	void Update(int x,int y,int id,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){t[p].push_back(id);return;}
		int mid=(l+r)>>1;
		Update(x,y,id,lson);Update(x,y,id,rson);
	}
	void Solve(int p,int l,int r){
		if(!t[p].empty()){
			Tx.Clear();Ty.Clear();tmp[0].clear();tmp[1].clear();
			for(int i=l;i<=r;i++)update(P[i].t,P[i].x);
			
			int p0=tmp[0].size()-1;Tx.Clear();
			sort(tmp[0].begin(),tmp[0].end());
			sort(t[p].begin(),t[p].end(),[](int x,int y){return Ans[x].y>Ans[y].y;});
			for(auto i:t[p]){
				while(p0>=0&&tmp[0][p0].fst>=Ans[i].y){Tx.Update(tmp[0][p0].scd,n-tmp[0][p0].fst,n-tmp[0][p0].fst,Tx.Root,0,n);p0--;}
				Ans[i].x=max(Ans[i].x,Tx.Query(Ans[i].x,Tx.Root,0,n));
			}
			
			int p1=tmp[1].size()-1;Ty.Clear();
			sort(tmp[1].begin(),tmp[1].end());
			sort(t[p].begin(),t[p].end(),[](int x,int y){return Ans[x].x>Ans[y].x;});
			for(auto i:t[p]){
				while(p1>=0&&tmp[1][p1].fst>=Ans[i].x){Ty.Update(tmp[1][p1].scd,n-tmp[1][p1].fst,n-tmp[1][p1].fst,Ty.Root,0,n);p1--;}
				Ans[i].y=max(Ans[i].y,Ty.Query(Ans[i].y,Ty.Root,0,n));
			}
			
		}
		if(l==r)return;int mid=(l+r)>>1;Solve(lson);Solve(rson);
	}
	#undef lson
	#undef rson
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Q=read();
	for(int i=1;i<=m;i++){a[i].x=read();a[i].y=read();a[i].s=1;}
	for(int i=1;i<=Q;i++){
		int op=read();
		if(op==1){int id=read();qnt++;Ans[qnt]=a[id];Ans[qnt].t=tot;}
		if(op==2)P[++tot]=(Node){read(),0,0,0};
		if(op==3)P[++tot]=(Node){read(),0,0,1};
		if(op==4){m++;a[m].x=read();a[m].y=read();a[m].s=tot+1;}
	}
	for(int i=1;i<=qnt;i++)if(Ans[i].s<=Ans[i].t)tree.Update(Ans[i].s,Ans[i].t,i,1,1,tot);
	if(tot)tree.Solve(1,1,tot);
	for(int i=1;i<=qnt;i++)printf("%d %d\n",Ans[i].x,Ans[i].y);
	return 0;
}