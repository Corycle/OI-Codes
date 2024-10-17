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
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
int h[N],a[N],id[N],st[N];
priority_queue<int>q[N];
struct edge{int to,next;}d[N];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void DFS(int x){
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;DFS(y);
		if(q[id[x]].size()<q[id[y]].size())swap(id[x],id[y]);
		int top=0;
		while(!q[id[y]].empty()){
			st[++top]=max(q[id[x]].top(),q[id[y]].top());
			q[id[x]].pop();q[id[y]].pop();
		}
		while(top)q[id[x]].push(st[top--]);
	}
	q[id[x]].push(a[x]);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)id[i]=i;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=2;i<=n;i++)Add(read(),i);
	DFS(1);
	ll ans=0;
	while(!q[id[1]].empty()){ans+=q[id[1]].top();q[id[1]].pop();}
	printf("%lld",ans);
	return 0;
}