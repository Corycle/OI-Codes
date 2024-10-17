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
const int Mod=998244353;
const int N=250005;
const int M=4;
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
int n,m,flag;
int a[N],b[N],c[N];
ll MOD(ll x){return x>=Mod?x-Mod:x;}
struct Matrix{
	ll a[M][M],tag,n,m;
	void Init(int A=0,int B=0){
		tag=0;n=A;m=B;
		memset(a,0,sizeof(a));
	}
	friend Matrix operator*(Matrix A,Matrix B){
		Matrix C;C.Init(A.n,B.m);C.tag=1;
		for(int i=0;i<C.n;i++){
			for(int j=0;j<C.m;j++){
				for(int k=0;k<A.m;k++){
					C.a[i][j]+=A.a[i][k]*B.a[k][j];
				}
				C.a[i][j]%=Mod;
			}
		}
		return C;
	}
	friend Matrix operator+(Matrix A,Matrix B){
		Matrix C;C.Init(A.n,A.m);
		for(int i=0;i<C.n;i++){
			for(int j=0;j<C.m;j++){
				C.a[i][j]=MOD(A.a[i][j]+B.a[i][j]);
			}
		}
		return C;
	}
}E,tmp;
struct Segment_Tree{
	Matrix t1[N*4],t2[N*4];
	void Pushup(int p){
		t2[p]=t2[p<<1]+t2[p<<1|1];
	}
	void Pushdown(int p){
		if(t1[p].tag){
			t1[p<<1]=t1[p]*t1[p<<1];
			t2[p<<1]=t1[p]*t2[p<<1];
			t1[p<<1|1]=t1[p]*t1[p<<1|1];
			t2[p<<1|1]=t1[p]*t2[p<<1|1];
			t1[p]=E;t1[p].tag=0;
		}
	}
	void Build(int p,int l,int r){
		t1[p]=E;t2[p].Init(4,1);
		if(l==r){
			t2[p].a[0][0]=a[l];
			t2[p].a[1][0]=b[l];
			t2[p].a[2][0]=c[l];
			t2[p].a[3][0]=1;
			return;
		}
		int mid=(l+r)>>1;
		Build(lson);Build(rson);
		Pushup(p);
	}
	void Update(int x,int y,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){
			t1[p]=tmp*t1[p];
			t2[p]=tmp*t2[p];
			return;
		}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,lson);Update(x,y,rson);
		Pushup(p);
	}
	void Ask(int x,int y,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){
			if(!flag){flag=1;tmp=t2[p];}
			else tmp=tmp+t2[p];
			return;
		}
		int mid=(l+r)>>1;Pushdown(p);
		Ask(x,y,lson);Ask(x,y,rson);
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();E.Init(4,4);
	for(int i=0;i<M;i++)E.a[i][i]=1;
	for(int i=1;i<=n;i++){
		a[i]=read();
		b[i]=read();
		c[i]=read();
	}
	m=read();
	tree.Build(1,1,n);
	for(int i=1;i<=m;i++){
		tmp=E;flag=0;
		int op=read(),l=read(),r=read();
		if(op==1)tmp.a[0][1]=1;
		if(op==2)tmp.a[1][2]=1;
		if(op==3)tmp.a[2][0]=1;
		if(op==4)tmp.a[0][3]=read();
		if(op==5)tmp.a[1][1]=read();
		if(op==6){tmp.a[2][3]=read();tmp.a[2][2]=0;}
		if(op==7){
			flag=0;tmp.Init(4,1);tree.Ask(l,r,1,1,n);
			printf("%lld %lld %lld\n",tmp.a[0][0],tmp.a[1][0],tmp.a[2][0]);
		}
		else tree.Update(l,r,1,1,n);
	}
	return 0;
}