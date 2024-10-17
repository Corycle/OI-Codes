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
#define y1 y_1
#define ll long long
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,flag,a[2][N],b[N];
struct Node{
	ll ans;
	int l,r,L,R,num,Max,lmax,rmax;
	void Init(){ans=l=r=L=R=num=Max=lmax=rmax=0;}
	friend Node operator+(Node A,Node B){
		Node C;C.Init();
		C.num=A.num+B.num;
		C.l=A.l;C.L=A.L;C.lmax=A.lmax;
		C.r=B.r;C.R=B.R;C.rmax=B.rmax;
		C.Max=max(max(A.Max,B.Max),max(a[0][A.r],a[1][A.r]));
		int dlt=max(max(A.rmax,B.lmax),max(a[0][A.r],a[1][A.r]));
		C.ans=A.ans+B.ans+a[0][A.r]+a[1][A.r]-dlt;
		if(dlt==A.R){
			C.num--;
			if(A.num==1){
				C.L=B.L;
				C.lmax=max(max(A.Max,B.lmax),max(a[0][A.r],a[1][A.r]));
			}
		}
		else if(dlt==B.L){
			C.num--;
			if(B.num==1){
				C.R=A.R;
				C.rmax=max(max(B.Max,A.rmax),max(a[0][A.r],a[1][A.r]));
			}
		}
		return C;
	}
};
Node Ans;
struct Segment_Tree{
	Node t[N*4];
	void Init(int p,int l){
		t[p].num=1;
		t[p].l=t[p].r=l;
		t[p].L=t[p].R=t[p].lmax=t[p].rmax=t[p].ans=b[l];
	}
	void Build(int p,int l,int r){
		if(l==r){Init(p,l);return;}
		int mid=(l+r)>>1;
		Build(lson);Build(rson);
		t[p]=t[p<<1]+t[p<<1|1];
	}
	void Change(int x,int p,int l,int r){
		if(l==r){Init(p,l);return;}
		int mid=(l+r)>>1;
		x<=mid?Change(x,lson):Change(x,rson);
		t[p]=t[p<<1]+t[p<<1|1];
	}
	void Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){Ans=(flag?Ans+t[p]:t[p]);flag=1;return;}
		int mid=(l+r)>>1;
		Query(x,y,lson);Query(x,y,rson);
	}
}tree;
char s[10];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<n;i++)a[0][i]=read();
	for(int i=1;i<n;i++)a[1][i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	tree.Build(1,1,n);
	while(m--){
		scanf("%s",s);
		if(s[0]=='C'){
			int x1=read(),y1=read(),x2=read(),y2=read(),val=read();
			if(x1==x2&&x1==1)a[0][min(y1,y2)]=val;
			if(x1==x2&&x1==2)a[1][min(y1,y2)]=val;
			if(y1==y2)b[y1]=val;
			tree.Change(min(y1,y2),1,1,n);
		}
		if(s[0]=='Q'){
			flag=0;Ans.Init();
			int l=read(),r=read();
			tree.Query(l,r,1,1,n);
			printf("%lld\n",Ans.ans);
		}
	}
	return 0;
}