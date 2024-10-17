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
#define lson t[p].l,l,mid
#define rson t[p].r,mid+1,r
using namespace std;
const int inf=2e9;
const int N=1505;
const int M=N*N;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m1,m2,Ans=inf;
int P[N],f[N][N],fst[N][N];
int a[N],b[M],sum[N],root[M];
struct Segment_Tree{
	int tot;
	struct Tree{int l,r,Max;}t[M*4];
	void Pushup(int p){
		t[p].Max=-inf;
		if(t[p].l)t[p].Max=max(t[p].Max,t[t[p].l].Max);
		if(t[p].r)t[p].Max=max(t[p].Max,t[t[p].r].Max);
	}
	void Update(int x,int y,int &p,int l,int r){
		if(!p)t[p=++tot].Max=-inf;
		if(l==r){
			t[p].Max=max(t[p].Max,y);
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid)Update(x,y,lson);
		if(x>mid) Update(x,y,rson);
		Pushup(p);
	}
	int Ask(int x,int y,int p,int l,int r){
		if(y<l||x>r||!p)return -inf;
		if(x<=l&&r<=y)return t[p].Max;
		int mid=(l+r)>>1;
		return max(Ask(x,y,lson),Ask(x,y,rson));
	}
}tree;
void Prepare(){
	for(int i=1;i<n;i++)sum[i]=sum[i-1]+P[i];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			b[++b[0]]=fst[i][j]=a[i]-sum[j-1];
		}
	}
	sort(b+1,b+b[0]+1);
	b[0]=unique(b+1,b+b[0]+1)-b-1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			fst[i][j]=lower_bound(b+1,b+b[0]+1,fst[i][j])-b;
			f[i][j]=1;
		}
	}
}
void Solve(int x,int y){
	int id=fst[x][y];
	if(y!=1)f[x][y]=max(f[x][y],tree.Ask(1,y-1,root[id],1,n)+1);
	Ans=min(Ans,m1*(y-f[x][y])+m2*(x-y)+min(m1,m2)*(n-x));
	tree.Update(y,f[x][y],root[id],1,n);
}
int main(){
//	freopen("string.in","r",stdin);
//	freopen("string.out","w",stdout);
	n=read();m1=read();m2=read();
	for(int i=1;i<n;i++)P[i]=read();
	for(int i=1;i<=n;i++)a[i]=read();
	Prepare();
	for(int i=1;i<=n;i++){
		int x=i,y=1;
		while(x<=n){
			Solve(x,y);
			x++;y++;
		}
	}
	printf("%d",Ans);
	return 0;
}