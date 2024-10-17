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
#include<set>
#define ll long long
#define set_it set<Node>::iterator
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e5+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Dist,a[N];
int n,m,b[N],fa[N],sum[N];
bool cmp(int x,int y){return a[x]>a[y];}
struct Node{
	ll val;int x;
	friend bool operator<(Node A,Node B){return A.val!=B.val?A.val<B.val:A.x<B.x;}
};
set<Node>F;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){a[i]=read();b[i]=i;sum[i]=1;F.insert((Node){a[i],i});}
	sort(b+1,b+n+1,cmp);
	for(int i=1;i<n;i++){
		int x=b[i];
		ll val=a[x]+2*sum[x]-n;
		F.erase((Node){a[x],x});
		set_it p=F.lower_bound((Node){val,0});
		if(p==F.end()||(*p).val!=val){puts("-1");return 0;}
		int y=(*p).x;fa[x]=y;sum[y]+=sum[x];Dist+=sum[x];
	}
	if(Dist!=a[b[n]]){puts("-1");return 0;}
	for(int i=1;i<=n;i++)if(fa[i])printf("%d %d\n",i,fa[i]);
	return 0;
}
