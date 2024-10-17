#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define inf 0x3f3f3f3f
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
//struct _{};
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,h[155],cnt,dfn[155],low[155],tot,jsb,fa[155];
struct edge{
	int to,next;
}d[10005];
void hqq_add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
pair<int,int>ans[10005];
void tarjan(int x){
	int i,j,k;
	dfn[x]=low[x]=++tot;
	for(i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		if(!dfn[y]){
			fa[y]=x;
			tarjan(y);
			low[x]=min(low[x],low[y]);
			if(low[y]>dfn[x]){
				ans[++jsb]=make_pair(x,y);
			}
		}
		else low[x]=min(low[x],dfn[y]);
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	for(i=1;i<=m;i++){
		int x=read(),y=read();
		hqq_add(x,y);
		hqq_add(y,x);
	}
	tarjan(1);
	sort(ans+1,ans+jsb+1);
	for(i=1;i<=jsb;i++){
		printf("%d %d\n",ans[i].first,ans[i].second);
	}
	return 0;
}