/*====Corycle====*/
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
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
const int N=400005;
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
ll Ans;
int n,m,tot,a[N];
struct Position{int x,y;}P[N];
/*10 Points*/
namespace Task1{
	ll Sum(ll x){return (1+x)*x/2;}
	void Main(){
		printf("%lld",Sum(m)*n+Sum(n)-n);
	}
}
/*30 Points*/
namespace Task2{
	int Cnt[N];int *cnt=Cnt+200000;
	int lmax[N],lmin[N],rmin[N],rmax[N];
	void Calc(int l,int r,int mid){
		lmin[mid+1]=inf;rmax[mid]=-inf;
		lmax[mid+1]=-inf;rmin[mid]=inf;
		for(int i=mid;i>=l;i--){
			lmax[i]=max(lmax[i+1],a[i]);
			lmin[i]=min(lmin[i+1],a[i]);
		}
		for(int i=mid+1;i<=r;i++){
			rmax[i]=max(rmax[i-1],a[i]);
			rmin[i]=min(rmin[i-1],a[i]);
		}
		for(int i=l;i<=mid;i++){
			int j=i+lmax[i]-lmin[i];
			if(j>mid&&rmax[j]<lmax[i]&&rmin[j]>lmin[i])Ans++;
		}
		int p1=mid,p2=mid;
		for(int i=l;i<=mid;i++)cnt[i-lmin[i]]=0;
		for(int i=mid+1;i<=r;i++)cnt[i-rmax[i]]=0;
		while(p1<r&&rmax[p1+1]<lmax[l]){p1++;cnt[p1-rmax[p1]]--;}
		while(p2<r&&rmin[p2+1]>lmin[l]){p2++;cnt[p2-rmax[p2]]++;}
		for(int i=l;i<=mid;i++){
			while(p1>mid&&rmax[p1]>lmax[i]){cnt[p1-rmax[p1]]++;p1--;}
			while(p2>mid&&rmin[p2]<lmin[i]){cnt[p2-rmax[p2]]--;p2--;}
			Ans+=max(cnt[i-lmin[i]],0);
		}
		for(int i=l;i<=mid;i++)cnt[i-lmin[i]]=0;
		for(int i=mid+1;i<=r;i++)cnt[i-rmax[i]]=0;
	}
	void Divide(int l,int r){
		int mid=(l+r)>>1;
		if(l==r){Ans++;return;}
		Divide(l,mid);Divide(mid+1,r);
		Calc(l,r,mid);reverse(a+l,a+r+1);
		if((r-l+1)&1)mid--;
		Calc(l,r,mid);reverse(a+l,a+r+1);
	}
	void Main(){
		for(int i=1;i<=tot;i++)a[i]=P[i].y;
		Divide(1,tot);
		printf("%lld",Ans);
	}
}
/*10 Points*/
namespace Task3{
	void Main(){
		for(int l=1;l<=tot;l++){
			int Xmax=-inf,Xmin=inf;
			int Ymax=-inf,Ymin=inf;
			for(int r=l;r<=tot;r++){
				Xmax=max(Xmax,P[r].x);
				Xmin=min(Xmin,P[r].x);
				Ymax=max(Ymax,P[r].y);
				Ymin=min(Ymin,P[r].y);
				if((Xmax-Xmin+1)*(Ymax-Ymin+1)==r-l+1)Ans++;
				if((Xmax-Xmin+1)*(Ymax-Ymin+1)>tot-l+1)break;
			}
		}
		printf("%lld",Ans);
	}
}
/*100 Points*/
namespace Task4{
	struct Tree{int Min,num,tag;};
	Tree Merge(Tree &A,Tree &B){
		Tree C=(Tree){0,0,0};
		C.Min=min(A.Min,B.Min);
		if(A.Min==C.Min)C.num+=A.num;
		if(B.Min==C.Min)C.num+=B.num;
		return C;
	}
	Tree Answer;
	struct Segment_Tree{
		Tree t[N*4];
		void update(int p,int x){
			t[p].tag+=x;
			t[p].Min+=x;
		}
		void Pushdown(int p){
			if(t[p].tag){
				update(p<<1,t[p].tag);
				update(p<<1|1,t[p].tag);
				t[p].tag=0;
			}
		}
		void Build(int p,int l,int r){
			if(l==r){t[p].num=1;return;}
			int mid=(l+r)>>1;
			Build(lson);Build(rson);
			t[p]=Merge(t[p<<1],t[p<<1|1]);
		}
		void Update(int x,int y,int z,int p,int l,int r){
			if(y<l||x>r)return;
			if(x<=l&&r<=y){update(p,z);return;}
			int mid=(l+r)>>1;Pushdown(p);
			Update(x,y,z,lson);Update(x,y,z,rson);
			t[p]=Merge(t[p<<1],t[p<<1|1]);
		}
		void Ask(int x,int y,int p,int l,int r){
			if(y<l||x>r)return;
			if(x<=l&&r<=y){
				if(!Answer.num)Answer=t[p];
				else Answer=Merge(Answer,t[p]);
				return;
			}
			int mid=(l+r)>>1;Pushdown(p);
			Ask(x,y,lson);Ask(x,y,rson);
		}
	}tree;
	int s[10];
	int Ask(int x,int y){
		if(x<1||x>n||y<1||y>m)return tot+1;
		return a[(x-1)*m+y];
	}
	void Solve(int x,int y,int r){
		int top=0;
		s[++top]=Ask(x,y);
		s[++top]=Ask(x+1,y);
		s[++top]=Ask(x,y+1);
		s[++top]=Ask(x+1,y+1);
		sort(s+1,s+top+1);
		while(s[top]>r)top--;
		for(int i=top;i>=1;i--){
			int t=((top-i+1)&1)?1:-1;
			tree.Update(s[i-1]+1,s[i],t,1,1,tot);
		}
	}
	void Main(){
		tree.Build(1,1,tot);
		for(int r=1;r<=tot;r++){
			int x=P[r].x,y=P[r].y;
			Solve(x-1,y-1,r);
			Solve(x-1,y,r);
			Solve(x,y-1,r);
			Solve(x,y,r);
			Answer=(Tree){0,0,0};
			tree.Ask(1,r,1,1,tot);
			Ans+=Answer.num;
		}
		printf("%lld",Ans);
	}
}
int main(){
//	freopen("veinminer.in","r",stdin);
//	freopen("veinminer.out","w",stdout);
	n=read();m=read();tot=n*m;
	int flag=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int x=read();
			a[(i-1)*m+j]=x;
			P[x].x=i;P[x].y=j;
			if(x!=(i-1)*m+j)flag=0;
		}
	}
	if(flag){Task1::Main();return 0;}
	if(n==1){Task2::Main();return 0;}
//	if(n*m<=1e8){Task3::Main();return 0;}
	Task4::Main();
	return 0;
}
/*
2 3
1 2 3
4 5 6

4 4
4 1 5 6
3 13 7 11
2 14 8 9
16 15 12 10
*/