#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<bitset>
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
int n,m,vis[1005],cnt,h[1005],tmp,ans;
struct edge{
	int to,next;
}d[10005];
void hqq_add(int x,int y){
	cnt++;
	d[cnt].to=y;
	d[cnt].next=h[x];
	h[x]=cnt;
}
void dfs(int x){
	int i,j,k;
	for(i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(vis[y]==0){
			tmp++;
			vis[y]=1;
			dfs(y);
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	for(i=1;i<=m;i++){
		j=read();k=read();
		hqq_add(j,k);
	}
	for(i=1;i<=n;i++){
		tmp=0;
		memset(vis,0,sizeof(vis));
        dfs(i);
        ans+=tmp;
	}
	ans=(n-1)*n/2-ans;
	printf("%d",ans);
	return 0;
}