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
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
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
int a[N],g[N],n,m;
struct Section{int l,r;}b[N];
struct tree{
	int tag,sum,l,r;
	int maxl,maxr,Max,Maxl,Maxr,maxl_r,maxr_l; 
	int minl,minr,Min,Minl,Minr,minl_r,minr_l;
	void Invert(){
		Max=-Max;Min=-Min;sum=-sum;tag^=1;
		swap(maxl,minl);maxl=-maxl;minl=-minl;
		swap(maxr,minr);maxr=-maxr;minr=-minr;
		swap(maxl_r,minl_r);swap(maxr_l,minr_l);
		swap(Max,Min);swap(Maxl,Minl);swap(Maxr,Minr);
	}
}t[N*4];
inline int Check_max(int x,int y,int z,int q,int w){
	if(x>=y&&x>=z&&x>=q&&x>=w)return 1;
	if(y>=x&&y>=z&&y>=q&&y>=w)return 2;
	if(z>=x&&z>=y&&z>=q&&z>=w)return 3;
	if(q>=x&&q>=y&&q>=z&&q>=w)return 4;
	return 5;
}
inline int Check_min(int x,int y,int z,int q,int w){
	if(x<=y&&x<=z&&x<=q&&x<=w)return 1;
	if(y<=x&&y<=z&&y<=q&&y<=w)return 2;
	if(z<=x&&z<=y&&z<=q&&z<=w)return 3;
	if(q<=x&&q<=y&&q<=z&&q<=w)return 4;
	return 5;
}
inline tree operator+(const tree& x,const tree& y){
	tree Ans;
	Ans.l=x.l;Ans.r=y.r;Ans.sum=x.sum+y.sum;Ans.tag=0;
	if(x.maxl>x.sum+y.maxl){Ans.maxl=x.maxl;Ans.maxl_r=x.maxl_r;}else{Ans.maxl=x.sum+y.maxl;Ans.maxl_r=y.maxl_r;}
	if(y.maxr>y.sum+x.maxr){Ans.maxr=y.maxr;Ans.maxr_l=y.maxr_l;}else{Ans.maxr=y.sum+x.maxr;Ans.maxr_l=x.maxr_l;}
	if(x.minl<x.sum+y.minl){Ans.minl=x.minl;Ans.minl_r=x.minl_r;}else{Ans.minl=x.sum+y.minl;Ans.minl_r=y.minl_r;}
	if(y.minr<y.sum+x.minr){Ans.minr=y.minr;Ans.minr_l=y.minr_l;}else{Ans.minr=y.sum+x.minr;Ans.minr_l=x.minr_l;}
	
	int type=Check_max(x.Max,y.Max,x.maxr+y.maxl,x.maxr+y.sum,x.sum+y.maxl);
	if(type==1){Ans.Max=x.Max;Ans.Maxl=x.Maxl;Ans.Maxr=x.Maxr;}
	else if(type==2){Ans.Max=y.Max;Ans.Maxl=y.Maxl;Ans.Maxr=y.Maxr;}
	else if(type==3){Ans.Max=x.maxr+y.maxl;Ans.Maxl=x.maxr_l;Ans.Maxr=y.maxl_r;}
	else if(type==4){Ans.Max=x.maxr+y.sum;Ans.Maxl=x.maxr_l;Ans.Maxr=y.r;}
	else {Ans.Max=x.sum+y.maxl;Ans.Maxl=x.l;Ans.Maxr=y.maxl_r;}
	
	type=Check_min(x.Min,y.Min,x.minr+y.minl,x.minr+y.sum,x.sum+y.minl);
	if(type==1){Ans.Min=x.Min;Ans.Minl=x.Minl;Ans.Minr=x.Minr;}
	else if(type==2){Ans.Min=y.Min;Ans.Minl=y.Minl;Ans.Minr=y.Minr;}
	else if(type==3){Ans.Min=x.minr+y.minl;Ans.Minl=x.minr_l;Ans.Minr=y.minl_r;}
	else if(type==4){Ans.Min=x.minr+y.sum;Ans.Minl=x.minr_l;Ans.Minr=y.r;}
	else {Ans.Min=x.sum+y.minl;Ans.Minl=x.l;Ans.Minr=y.minl_r;}
	
	return Ans;
}
void Build(int now,int l,int r){
	if(l==r){
		t[now].l=t[now].r=l;
		t[now].Maxl=t[now].Maxr=t[now].Minl=t[now].Minr=l;
		t[now].Max=t[now].Min=t[now].sum=a[l];t[now].tag=0;
		t[now].maxl=t[now].maxr=t[now].minl=t[now].minr=a[l];
		t[now].maxl_r=t[now].maxr_l=t[now].minl_r=t[now].minr_l=l;
		return;
	}
	int mid=l+r>>1;
	Build(now*2,l,mid);
	Build(now*2+1,mid+1,r);
	t[now]=t[now*2]+t[now*2+1];
}
void Change(int now,int l,int r,int p){
	if(l==r){
		t[now].l=t[now].r=l;
		t[now].Maxl=t[now].Maxr=t[now].Minl=t[now].Minr=l;
		t[now].Max=t[now].Min=t[now].sum=a[l];t[now].tag=0;
		t[now].maxl=t[now].maxr=t[now].minl=t[now].minr=a[l];
		t[now].maxl_r=t[now].maxr_l=t[now].minl_r=t[now].minr_l=l;
		return;
	}
	int mid=l+r>>1;
	if(p<=mid)Change(now*2,l,mid,p);
	else Change(now*2+1,mid+1,r,p);
	t[now]=t[now*2]+t[now*2+1];
}
inline void pushdown(int x){
	if(t[x].tag){
		t[x].tag=0;
		t[x*2].Invert();
		t[x*2+1].Invert();
	}
}
void Ask(int now,int l,int r,int ll,int rr){
	if(l>rr||r<ll)return;
	if(ll<=l&&rr>=r){
		g[++g[0]]=now;
		return;
	}
	int mid=l+r>>1;
	pushdown(now);
	Ask(now*2,l,mid,ll,rr);
	Ask(now*2+1,mid+1,r,ll,rr);
}
void Change_tag(int now,int l,int r,int ll,int rr){
	if(l>rr||r<ll)return;
	if(ll<=l&&rr>=r){
		t[now].Invert();
		return;
	}
	int mid=l+r>>1;
	pushdown(now);
	Change_tag(now*2,l,mid,ll,rr);
	Change_tag(now*2+1,mid+1,r,ll,rr);
	t[now]=t[now*2]+t[now*2+1];
}
void solve(int L,int R,int K){
	tree Ans,x;
	int ans=0,tot=0;
	for(int i=1;i<=K;++i){
		g[0]=0;
		Ask(1,1,n,L,R);
		Ans=t[g[1]];
		for(int j=2;j<=g[0];++j){
			x=Ans;Ans=x+t[g[j]];
		}
		if(Ans.Max<=0)break;
		ans+=Ans.Max;
		b[++tot]=(Section){Ans.Maxl,Ans.Maxr};
		Change_tag(1,1,n,Ans.Maxl,Ans.Maxr);
	}
	for(int i=1;i<=tot;++i){
		Change_tag(1,1,n,b[i].l,b[i].r);
	}
	printf("%d\n",ans);
}
int main(){
	n=read();
	for(int i=1;i<=n;++i)a[i]=read();
	Build(1,1,n);
	m=read();
	for(int i=1;i<=m;++i){
		int op=read();
		if(op==0){
			int x=read(),y=read();
			a[x]=y;Change(1,1,n,x);
		}
		if(op==1){
			int x=read(),y=read(),z=read();
			solve(x,y,z);
		}
	}
	return 0;
}