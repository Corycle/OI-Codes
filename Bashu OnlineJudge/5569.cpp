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
const int N=500005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>Del[N];
int n,m,cnt,tot;
int h[N],a[N],L[N],R[N],id[N];
struct Point{ll x,y;}P[N];
struct edge{int to,next;}d[N];
struct Ques{ll x,k,id,ans;}Q[N];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
bool cmp(int x,int y){return P[id[x]].x<P[id[y]].x;}
bool Cmp(int x,int y){return L[x]<L[y];}
ll Cross(Point A,Point B,Point C){
	return (A.x-C.x)*(B.y-C.y)-(A.y-C.y)*(B.x-C.x);
}
ll GetPos(int x,int t){return P[t].y-P[t].x*x;}
void DFS(int x){
	L[x]=++tot;
	for(int i=h[x];i;i=d[i].next)DFS(d[i].to);
	R[x]=tot;
}
struct Tree{
	int Size,lst;
	vector<int>st;
	void Insert(int x){
		while(Size>=2&&Cross(P[x],P[st[Size-1]],P[st[Size-2]])>=0){Size--;st.pop_back();}
		Size++;st.push_back(x);
	}
	ll Query(int x){
		if(!Size)return inf;
		while(lst<Size-1&&GetPos(x,st[lst+1])<GetPos(x,st[lst]))lst++;
		return GetPos(x,st[lst]);
	}
};
struct Segment_Tree{
	Tree t[N*4];
	void Insert(int x,int y,int z,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){t[p].Insert(z);return;}
		int mid=(l+r)>>1;
		Insert(x,y,z,lson);Insert(x,y,z,rson);
	}
	ll Query(int x,int y,int p,int l,int r){
		if(x<l||x>r)return inf;
		if(l==r)return t[p].Query(y);
		int mid=(l+r)>>1;
		return min(t[p].Query(y),min(Query(x,y,lson),Query(x,y,rson)));
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();P[0].y=read();a[++a[0]]=1;
	for(int i=2;i<=n;i++){
		int op=read(),fa=read()+1;id[i]=read();Add(fa,i);
		if(op==0){
			ll x=read();read();read();ll c=read();
			P[id[i]].x=2*x;P[id[i]].y=x*x+c;a[++a[0]]=i;
		}
		if(op==1)Del[id[i]].push_back(i);
	}
	DFS(1);
	sort(a+1,a+a[0]+1,cmp);
	for(int i=1;i<=a[0];i++){
		int x=id[a[i]],lst=L[a[i]]; 
		sort(Del[x].begin(),Del[x].end(),Cmp);
		for(auto y:Del[x]){
			if(lst<L[y])tree.Insert(lst,L[y]-1,x,1,1,n);
			lst=max(lst,R[y]+1);
		}
		if(lst<=R[a[i]])tree.Insert(lst,R[a[i]],x,1,1,n);
	}
	for(int i=1;i<=m;i++){Q[i].id=i;Q[i].x=read()+1;Q[i].k=read();}//Ans=min{b-K*a+K*K};
	sort(Q+1,Q+m+1,[](Ques x,Ques y){return x.k<y.k;});
	for(int i=1;i<=m;i++)Q[i].ans=tree.Query(L[Q[i].x],Q[i].k,1,1,n)+Q[i].k*Q[i].k;
	sort(Q+1,Q+m+1,[](Ques x,Ques y){return x.id<y.id;});
	for(int i=1;i<=m;i++)printf("%lld\n",Q[i].ans);
	return 0;
}