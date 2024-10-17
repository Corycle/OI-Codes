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
struct _{
	int to,next;
}a[100005];
//vector<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int n,m,tot,low[5005],dfn[5005],p[5005],st[5005],top,ans1[5005],ans2[5005],h[5005],cnt;
void hqq_add(int x,int y){
	cnt++;
	a[cnt].to=y;
	a[cnt].next=h[x];
	h[x]=cnt;
}
void hqq_dfs(int rt){//tarjan
	int i,j,k;
	p[rt]=1;
	low[rt]=dfn[rt]=++tot;
	st[++top]=rt;
	for(i=h[rt];i;i=a[i].next){
		j=a[i].to;
		if(dfn[j]==0){
			hqq_dfs(j);
			low[rt]=min(low[rt],low[j]);
		}
		else if(p[j]){
			low[rt]=min(low[rt],dfn[j]);
		}
	}
	if(low[rt]==dfn[rt]){
		int t,t1=0;
		do{
			t=st[top--];
			p[t]=0;
			t1++;
			ans2[t1]=t;
		}while(t!=rt);
		if(ans1[0]<t1){
			for(i=1;i<=t1;i++)ans1[i]=ans2[i];
			ans1[0]=t1;
		}
		else if(ans1[0]==t1){
			sort(ans1+1,ans1+t1+1);
			sort(ans2+1,ans2+t1+1);
			for(i=1;i<=t1;i++){
				if(ans1[i]>ans2[i]){
					for(j=1;j<=t1;j++)ans1[j]=ans2[j];
					break;
				}
			}
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k,t;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++){
		scanf("%d%d%d",&j,&k,&t);
		hqq_add(j,k);
		if(t==2)hqq_add(k,j);
	}
	for(i=1;i<=n;i++){
		if(dfn[i]==0){
			hqq_dfs(i);
		}
	}
	printf("%d\n",ans1[0]);
	sort(ans1+1,ans1+ans1[0]+1);
	for(i=1;i<=ans1[0];i++)printf("%d ",ans1[i]);
	return 0;
}