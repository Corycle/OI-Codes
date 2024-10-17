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
int n,m,a[105][105],b[105],low[105],dfn[105],p[105],rd[105],cd[105],st[105],tot,top,num,ans1,ans2;
void hqq_dfs(int rt){//tarjan
	int i,j,k,t;
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
		while(1){
			scanf("%d",&j);
			if(j==0)break;
			a[i][j]=1;
		}
	}
	for(i=1;i<=n;i++)if(dfn[i]==0)hqq_dfs(i);
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			if(a[i][j]&&b[i]!=b[j]){
				cd[b[i]]++;
				rd[b[j]]++;
			}
		}
	}
	for(i=1;i<=num;i++){
		if(rd[i]==0)ans1++;
		if(cd[i]==0)ans2++;
	}
	if(num==1)printf("1\n0");
	else printf("%d\n%d",ans1,max(ans2,ans1));
	return 0;
}