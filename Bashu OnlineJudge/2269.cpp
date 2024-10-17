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
using namespace std;
//struct _{};
//vector<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int n,m,a[1005][1005],tot,low[1005],dfn[1005],p[1005],ans,rd[1005],b[1005],num,st[1005],top;
void hqq_dfs(int rt){//tarjan
	int i,j,k;
	p[rt]=1;
	low[rt]=dfn[rt]=++tot;
	st[++top]=rt;
	for(i=1;i<=n;i++){
		if(a[rt][i]==1){
			if(dfn[i]==0){
				hqq_dfs(i);
				low[rt]=min(low[rt],low[i]);
			}
			else if(p[i]){
				low[rt]=min(low[rt],dfn[i]);
			}
		}
	}
	if(low[rt]==dfn[rt]){
		num++;
		int t;
		do{
			t=st[top--];
			p[t]=0;
			b[t]=num;
		}while(t!=rt);
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			scanf("%d",&a[i][j]);
		}
	}
	for(i=1;i<=n;i++){
		if(dfn[i]==0){
			hqq_dfs(i);
		}
	}
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			if(a[i][j]&&b[i]!=b[j])rd[b[j]]++;
		}
	}
	for(i=1;i<=num;i++)if(rd[i]==0)ans++;
	printf("%d",ans);
	return 0;
}