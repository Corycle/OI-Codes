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
}d[400005];
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int n,h[200005],cnt,ans[200005],num[200005],sum[200005],vis[200005],s,minn=0xfffff;
void hqq_add(int x,int y){
	cnt++;
	d[cnt].to=y;
	d[cnt].next=h[x];
	h[x]=cnt;
}
void hqq_dp(int rt){
	int i,j,k;
	vis[rt]=sum[rt]=1;
	for(i=h[rt];i;i=d[i].next){
		j=d[i].to;
		if(vis[j])continue;
		hqq_dp(j);
		sum[rt]+=sum[j];
		ans[rt]=max(ans[rt],sum[j]);
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	scanf("%d",&n);
	for(i=1;i<n;i++){
		scanf("%d%d",&j,&k);
		hqq_add(j,k);
		hqq_add(k,j);
	}
	hqq_dp(1);
	for(i=0;i<n;i++){
		ans[i]=max(ans[i],sum[1]-sum[i]);
		num[ans[i]]++;
		minn=min(minn,ans[i]);
	}
	printf("%d %d\n",minn,num[minn]);
	for(i=0;i<n;i++){
		if(ans[i]==minn)printf("%d ",i);
	}
	return 0;
}