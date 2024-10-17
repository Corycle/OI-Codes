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
const int N=500005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int b[N];
int n,m,tot,Ans;
struct Node{int l,r;}P[N];
bool cmp(Node A,Node B){return A.r!=B.r?A.r<B.r:A.l>B.l;}
struct BIT{
	int c[N];
	int lowbit(int x){return x&(-x);}
	void Add(int x,int y){for(;x<=tot;x+=lowbit(x))c[x]=max(c[x],y);}
	int Ask(int x){int ans=0;for(;x>=1;x-=lowbit(x))ans=max(ans,c[x]);return ans;}
}tree;
int main(){
//	freopen("game.in","r",stdin);
//	freopen("game.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		P[i].l=read();
		P[i].r=read();
		b[++tot]=P[i].l;
	}
	sort(b+1,b+tot+1);
	sort(P+1,P+n+1,cmp);
	tot=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++){
		P[i].l=lower_bound(b+1,b+tot+1,P[i].l)-b;
		int tmp=tree.Ask(tot-P[i].l+1)+1;
		tree.Add(tot-P[i].l+1,tmp);
		Ans=max(Ans,tmp);
	}
	printf("%d",Ans);
	return 0;
}