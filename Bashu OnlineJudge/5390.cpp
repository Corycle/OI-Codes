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
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans,tot;
int L[N],R[N];
struct Node{int l,r;}a[N];
bool cmp(Node A,Node B){return A.l<B.l;}
struct BIT{
	int c[N];
	int lowbit(int x){return x&(-x);}
	void Add(int x,int y){for(;x<=n;x+=lowbit(x))c[x]+=y;}
	int Ask(int x){int ans=0;for(;x>=1;x-=lowbit(x))ans+=c[x];return ans;}
}U,D;
void DFS(int id,int sum){
	if(sum>Ans)return;
	if(id>tot){Ans=min(Ans,sum);return;}
	int dlt1=min(U.Ask(a[id].r-1)-U.Ask(a[id].l),D.Ask(n)-D.Ask(a[id].l)+U.Ask(n)-U.Ask(a[id].r));
	int dlt2=min(D.Ask(a[id].r-1)-D.Ask(a[id].l),U.Ask(n)-U.Ask(a[id].l)+D.Ask(n)-D.Ask(a[id].r));
	U.Add(a[id].r,1);DFS(id+1,sum+dlt1);U.Add(a[id].r,-1);
	D.Add(a[id].r,1);DFS(id+1,sum+dlt2);D.Add(a[id].r,-1);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		n=read();Ans=inf;tot=0;
		for(int i=1;i<=n;i++)L[i]=R[i]=0;
		for(int i=1;i<=n;i++){int x=read();if(!L[x])L[x]=i;else R[x]=i;}
		for(int i=1;i<=n;i++)if(L[i]&&R[i])a[++tot]=(Node){L[i],R[i]};
		sort(a+1,a+tot+1,cmp);DFS(1,0);printf("%d\n",Ans);
	}
	return 0;
}