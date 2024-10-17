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
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
double a[N],b[N];
struct Tree{
	int c;
	double v[4],S,T;
	/*
		v0=sum(xi^2)
		v1=sum(xi*yi)
		v2=sum(xi)
		v3=sum(yi)
	*/
	friend Tree operator+(Tree A,Tree B){
		for(int i=0;i<4;i++)A.v[i]+=B.v[i];
		A.c=A.S=A.T=0;
		return A;
	}
}Ans;
double Sum1(double x){return x*(x+1)/2;}
double Sum2(double x){return x*(x+1)*(2*x+1)/6;}
struct Segment_Tree{
	Tree t[N*4];
	void update(int p,int l,int r,double S,double T){
		t[p].S+=S;t[p].T+=T;
		t[p].v[0]+=(r-l+1)*S*S+t[p].v[2]*S*2;
		t[p].v[1]+=(r-l+1)*S*T+t[p].v[2]*T+t[p].v[3]*S;
		t[p].v[2]+=(r-l+1)*S;
		t[p].v[3]+=(r-l+1)*T;
	}
	void Set(int p,int l,int r){
		t[p].c=1;t[p].S=t[p].T=0;
		t[p].v[0]=Sum2(r)-Sum2(l-1);
		t[p].v[1]=Sum2(r)-Sum2(l-1);
		t[p].v[2]=Sum1(r)-Sum1(l-1);
		t[p].v[3]=Sum1(r)-Sum1(l-1);
	}
	void Pushdown(int p,int l,int r){
		int mid=(l+r)>>1;
		if(t[p].c){Set(lson);Set(rson);}
		update(lson,t[p].S,t[p].T);
		update(rson,t[p].S,t[p].T);
		t[p].c=t[p].S=t[p].T=0;
	}
	void Build(int p,int l,int r){
		if(l==r){t[p].v[0]=a[l]*a[l];t[p].v[1]=a[l]*b[l];t[p].v[2]=a[l];t[p].v[3]=b[l];return;}
		int mid=(l+r)>>1;Build(lson);Build(rson);t[p]=t[p<<1]+t[p<<1|1];
	}
	void Update(int x,int y,int S,int T,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){update(p,l,r,S,T);return;}
		int mid=(l+r)>>1;Pushdown(p,l,r);
		Update(x,y,S,T,lson);Update(x,y,S,T,rson);
		t[p]=t[p<<1]+t[p<<1|1];
	}
	void Change(int x,int y,int S,int T,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){Set(p,l,r);update(p,l,r,S,T);return;}
		int mid=(l+r)>>1;Pushdown(p,l,r);
		Change(x,y,S,T,lson);Change(x,y,S,T,rson);
		t[p]=t[p<<1]+t[p<<1|1];
	}
	void Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){Ans=Ans+t[p];return;}
		int mid=(l+r)>>1;Pushdown(p,l,r);
		Query(x,y,lson);Query(x,y,rson);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	tree.Build(1,1,n);
	while(m--){
		int op=read(),l=read(),r=read();
		if(op==1){
			for(int i=0;i<4;i++)Ans.v[i]=0;
			tree.Query(l,r,1,1,n);
			double A=Ans.v[1]-Ans.v[2]*Ans.v[3]/(r-l+1);
			double B=Ans.v[0]-Ans.v[2]*Ans.v[2]/(r-l+1);
			printf("%.10lf\n",A/B);
		}
		if(op==2){
			int S=read(),T=read();
			tree.Update(l,r,S,T,1,1,n);
		}
		if(op==3){
			int S=read(),T=read();
			tree.Change(l,r,S,T,1,1,n);
		}
	}
	return 0;
}