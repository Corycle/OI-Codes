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
struct edge{
	int to,next;
}d[500005];
//vector<_>_;
//stack<_>_;
//queue<int>q;
//deque<_>_;
//priority_queue<int>q;
priority_queue<int,vector<int>,greater<int> >q;
int h[100005],cnt,n,m,ans[100005],num,r[100005];
void hqq_add(int x,int y){
	cnt++;
	d[cnt].to=y;
	d[cnt].next=h[x];
	h[x]=cnt;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	scanf("%d%d",&n,&m);
	int i,j,k;
	for(i=1;i<=m;i++){
		scanf("%d%d",&j,&k);
		hqq_add(j,k);
		r[k]++;
	}
	for(i=1;i<=n;i++){
		if(r[i]==0)q.push(i);
	}
	while(!q.empty()){
		int x=q.top();
		q.pop();
		ans[++num]=x;
		for(i=h[x];i;i=d[i].next){
			r[d[i].to]--;
			if(r[d[i].to]==0)q.push(d[i].to);
		}
	}
	if(num!=n){
		printf("NO SOLUTION");
		return 0;
	}
	for(i=1;i<=n;i++)printf("%d ",ans[i]);
	return 0;
}