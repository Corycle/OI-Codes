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
const ll inf=9e18;
const int N=5e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,b[N],id[N],st[N];
ll a[N],K[N],B[N],sum[N],Ans[N];
struct Ques{int l,r,x,id;}Q[N];
struct Node{int x,id;};
bool cmp1(Ques A,Ques B){return A.x>B.x;}
bool cmp2(Ques A,Ques B){return A.id<B.id;}
double Slope(int x,int y){
	if(K[x]==K[y])return inf;
	return (double)(B[x]-B[y])/(K[x]-K[y]);
}
struct Segment_Tree{
	vector<Node>t[N*4];
	void Insert(int x,int y,Node F,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){t[p].push_back(F);return;}
		int mid=(l+r)>>1;
		Insert(x,y,F,lson);Insert(x,y,F,rson);
	}
	void Solve(int p,int l,int r){
		if(l==r){
			for(auto F:t[p])Ans[F.id]=min(Ans[F.id],K[l]*F.x+B[l]);
			return;
		}
		int mid=(l+r)>>1;
		Solve(lson);Solve(rson);
		int tp=l-1,t0=l,t1=mid+1;
		while(t0<=mid&&t1<=r){
			if(a[id[t0]]<a[id[t1]])b[++tp]=id[t0++];
			else b[++tp]=id[t1++];
		}
		while(t0<=mid)b[++tp]=id[t0++];
		while(t1<=r)b[++tp]=id[t1++];
		for(int i=l;i<=r;i++)id[i]=b[i];
		int top=0,num=1;
		for(int i=l;i<=r;i++){
			while(top>1&&Slope(st[top-1],st[top])>Slope(st[top],id[i]))top--;
			st[++top]=id[i];
		}
		for(auto F:t[p]){
			while(num<top&&-Slope(st[num],st[num+1])>=F.x)num++;
			Ans[F.id]=min(Ans[F.id],K[st[num]]*F.x+B[st[num]]);
		}
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();id[i]=i;
		sum[i]=sum[i-1]+a[i];
		K[i]=a[i];B[i]=a[i]*i-sum[i];
	}
	m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();Ans[i]=inf;
		Q[i]=(Ques){max(y-x+1,1),y,x-y,i};
	}
	sort(Q+1,Q+m+1,cmp1);
	for(int i=1;i<=m;i++){
		tree.Insert(Q[i].l,Q[i].r,(Node){Q[i].x,Q[i].id},1,1,n);
	}
	tree.Solve(1,1,n);
	sort(Q+1,Q+m+1,cmp2);
	for(int i=1;i<=m;i++)printf("%lld\n",Ans[i]+sum[Q[i].r]);
	return 0;
}