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
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans,ans[N];
int n,m,a[N],b[N];
bool cmp(int x,int y){return a[x]!=a[y]?a[x]>a[y]:x>y;}
struct BIT{
	int c[N];
	int lowbit(int x){return x&(-x);}
	void Clear(){for(int i=1;i<=m;i++)c[i]=0;}
	void Add(int x,int y){for(;x<=m;x+=lowbit(x))c[x]+=y;}
	int Ask(int x){int ans=0;for(;x>=1;x-=lowbit(x))ans+=c[x];return ans;}
	int Query(int l,int r){return Ask(r)-Ask(l-1);}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=n+1;
	for(int i=1;i<=n;i++){a[i]=read()+1;b[i]=i;Ans+=tree.Query(a[i]+1,m);tree.Add(a[i],1);}
	tree.Clear();
	sort(b+1,b+n+1,cmp);
	for(int i=m-1,p=1;i>=1;i--){
		while(p<=n&&a[b[p]]>=i){Ans-=tree.Ask(b[p]-1);tree.Add(b[p],1);p++;}
		ans[i]=Ans;
	}
	for(int i=1;i<m;i++)printf("%lld\n",ans[i]);
	return 0;
}
