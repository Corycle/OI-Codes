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
struct hqq_edge{
	int to,next;
}d[32005];
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int n,cnt,s,h[16005],ans[16005],sum[16005],vis[16005],v[16005],maxx;
void hqq_add(int x,int y){
	cnt++;
	d[cnt].to=y;
	d[cnt].next=h[x];
	h[x]=cnt;
}
void hqq_dp(int rt){
	int i,j,k;
	vis[rt]=1;
	ans[rt]=v[rt];
	for(i=h[rt];i;i=d[i].next){
		j=d[i].to;
		if(vis[j])continue;
		hqq_dp(j);
		if(ans[j]>0)ans[rt]+=ans[j];
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	scanf("%d",&n);
	for(i=1;i<=n;i++)scanf("%d",&v[i]);
	for(i=1;i<n;i++){
		scanf("%d%d",&j,&k);
		hqq_add(j,k);
		hqq_add(k,j);
	}
	hqq_dp(1);
	for(i=1;i<=n;i++){
		maxx=max(maxx,ans[i]);
	}
	printf("%d",maxx);
	return 0;
}