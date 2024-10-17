/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
int n,m,a[N];
struct Section{int l,r,sum;};
struct Tree{int tag;Section sum,lmax,lmin,rmax,rmin,midmax,midmin;};
inline Section Sum(Section A,Section B){return (Section){A.l,B.r,A.sum+B.sum};}
inline Section Max(Section A,Section B){if(A.sum>B.sum)return A;else return B;}
inline Section Min(Section A,Section B){if(A.sum<B.sum)return A;else return B;}
struct Segment_Tree{
	Tree t[N*4];
	inline void Init(int p,int data,int pos){
		t[p].sum=(Section){pos,pos,data};
		t[p].lmax=(Section){pos,pos,data};
		t[p].lmin=(Section){pos,pos,data};
		t[p].rmax=(Section){pos,pos,data};
		t[p].rmin=(Section){pos,pos,data};
		t[p].midmax=(Section){pos,pos,data};
		t[p].midmin=(Section){pos,pos,data};
	}
	inline void Update(int p){
		t[p].tag^=1;
		t[p].sum.sum*=-1;
		swap(t[p].lmax,t[p].lmin);
		swap(t[p].rmax,t[p].rmin);
		swap(t[p].midmax,t[p].midmin);
		t[p].lmax.sum*=-1;t[p].lmin.sum*=-1;
		t[p].rmax.sum*=-1;t[p].rmin.sum*=-1;
		t[p].midmax.sum*=-1;t[p].midmin.sum*=-1;
	}
	inline void Pushdown(int p){
		if(t[p].tag){
			t[p].tag=0;
			Update(p<<1);
			Update(p<<1|1);
		}
	}
	inline Tree Pushup(Tree l,Tree r){
		Tree p;p.tag=0;
		p.sum=Sum(l.sum,r.sum);
		p.lmax=Max(l.lmax,Sum(l.sum,r.lmax));
		p.lmin=Min(l.lmin,Sum(l.sum,r.lmin));
		p.rmax=Max(r.rmax,Sum(l.rmax,r.sum));
		p.rmin=Min(r.rmin,Sum(l.rmin,r.sum));
		p.midmax=Max(Max(l.midmax,r.midmax),Sum(l.rmax,r.lmax));
		p.midmin=Min(Min(l.midmin,r.midmin),Sum(l.rmin,r.lmin));
		return p;
	}
	inline void Change(int x,int y,int p,int l,int r){
		if(x<l||x>r)return;
		if(l==r){Init(p,y,l);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Change(x,y,lson);Change(x,y,rson);
		t[p]=Pushup(t[p<<1],t[p<<1|1]);
	}
	inline Tree Ask(int x,int y,int p,int l,int r){
		if(x<=l&&r<=y){return t[p];}
		int mid=(l+r)>>1;Pushdown(p);
		if(y<=mid)return Ask(x,y,lson);
		if(x>mid) return Ask(x,y,rson);
		return Pushup(Ask(x,y,lson),Ask(x,y,rson));
	}
	inline void Rev(int x,int y,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){Update(p);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Rev(x,y,lson);Rev(x,y,rson);
		t[p]=Pushup(t[p<<1],t[p<<1|1]);
	}
}tree;
int main(){
//	freopen("zgg.in","r",stdin);
//	freopen("zgg.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		tree.Change(i,a[i],1,1,n);
	}
	m=read();
	while(m--){
		int op=read();
		if(op==0){
			int x=read(),y=read();a[x]=y;
			tree.Change(x,y,1,1,n);
		}
		if(op==1){
			queue<Section>q;
			int x=read(),y=read(),k=read(),ans=0;
			while(k--){
				Tree p=tree.Ask(x,y,1,1,n);
				if(p.midmax.sum<0)break;
				ans+=p.midmax.sum;q.push(p.midmax);
				tree.Rev(p.midmax.l,p.midmax.r,1,1,n);
			}
			while(q.size()){
				Section p=q.front();q.pop();
				tree.Rev(p.l,p.r,1,1,n);
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
