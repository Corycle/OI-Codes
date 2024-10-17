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
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,Ans,cnt[N];
struct Node{int id,a,b,c;}P[N],tmp[N];
bool cmpA(Node A,Node B){return A.a<B.a;}
bool cmpB(Node A,Node B){return A.b<B.b;}
bool cmpC(Node A,Node B){return A.c<B.c;}
struct BIT{
	int c[N];
	int lowbit(int x){return x&(-x);}
	void Clear(){for(int i=1;i<=n;i++)c[i]=0;}
	void Add(int x,int y){for(;x<=n;x+=lowbit(x))c[x]+=y;}
	int Ask(int x){int ans=0;for(;x>=1;x-=lowbit(x))ans+=c[x];return ans;}
}tree;
void CDQ(int l,int r){
	if(l==r)return;
	int mid=(l+r)>>1;
	int p1=l,p2=mid+1;
	CDQ(l,mid);CDQ(mid+1,r);
	while(p1<=mid&&p2<=r){
		if(P[p1].b<P[p2].b){tree.Add(P[p1].c,1);p1++;}
		else{cnt[P[p2].id]+=tree.Ask(P[p2].c);p2++;}
	}
	for(int i=p2;i<=r;i++)cnt[P[i].id]+=tree.Ask(P[i].c);
	for(int i=l;i<p1;i++)tree.Add(P[i].c,-1);
	sort(P+l,P+r+1,cmpB);
}
void Solve1(){Ans+=n;}
void Solve2(){
	Ans+=n*(n-1)/2;
	for(int i=1;i<=n;i++)Ans-=cnt[i];
}
void Solve3(){
	ll SumA=0,SumB=0;
	Ans+=n*(n-1)*(n-2)/6;
	for(int i=1;i<=n;i++)SumA+=cnt[i]*(cnt[i]-1)/2;
	
	sort(P+1,P+n+1,cmpA);
	for(int i=1;i<=n;i++){
		ll sum=tree.Ask(P[i].b);
		SumB+=sum*(sum-1)/2;
		tree.Add(P[i].b,1);
	}
	tree.Clear();
	
	sort(P+1,P+n+1,cmpB);
	for(int i=1;i<=n;i++){
		ll sum=tree.Ask(P[i].c);
		SumB+=sum*(sum-1)/2;
		tree.Add(P[i].c,1);
	}
	tree.Clear();
	
	sort(P+1,P+n+1,cmpC);
	for(int i=1;i<=n;i++){
		ll sum=tree.Ask(P[i].a);
		SumB+=sum*(sum-1)/2;
		tree.Add(P[i].a,1);
	}
	tree.Clear();
	
	SumB-=SumA*3;Ans-=SumA+SumB;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)P[i].id=i;
	for(int i=1;i<=n;i++)P[i].a=read();
	for(int i=1;i<=n;i++)P[i].b=read();
	for(int i=1;i<=n;i++)P[i].c=read();
	sort(P+1,P+n+1,cmpA);CDQ(1,n);
	Solve1();Solve2();Solve3();
	printf("%lld",Ans);
	return 0;
}