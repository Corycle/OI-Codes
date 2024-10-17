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
const ll INF=1e18;
const int N=1e5+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll m;
int n,cnt,a[N],h[N],Ans[N];
struct edge{int to,next;}d[N];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
struct Node{
	int val;ll num;
	friend Node operator+(Node A,Node B){
		if(A.val<B.val){A.val=B.val;A.num=B.num;}
		else if(A.val==B.val)A.num=min(A.num+B.num,INF);
		return A;
	}
}F[N];
struct Tree{
	Node c[N];
	int lowbit(int x){return x&(-x);}
	void Add(int x,Node p){for(;x<N;x+=lowbit(x))c[x]=c[x]+p;}
	Node Ask(int x){Node Ans=(Node){0,0};for(;x>=1;x-=lowbit(x))Ans=Ans+c[x];return Ans;}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();tree.Add(1,(Node){0,1});
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=n;i>=1;i--){
		F[i]=tree.Ask(n-a[i]+1);
		Add(++F[i].val,i);
		tree.Add(n-a[i]+1,F[i]);
	}
	for(int x=tree.Ask(n).val,tmp=0;x>=1;x--){
		for(int i=h[x];i;i=d[i].next){
			int p=d[i].to;
			if(F[p].num<m)m-=F[p].num;
			else{
				Ans[a[p]]=1;
				while(tmp<p)F[tmp++]=(Node){0,0};
				break;
			}
		}
	}
	printf("%d\n",n-tree.Ask(n).val);
	for(int i=1;i<=n;i++)if(!Ans[i])printf("%d\n",i);
	return 0;
}
