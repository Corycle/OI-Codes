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
int n,m,monkey[1005],x[1005],y[1005],cnt,g[1005],ans;
double maxx;
struct edge{
	int s,t;
	double data;
}d[1000005];
bool cmp(edge a,edge b){
	return a.data<b.data;
}
int find(int rt){
	if(g[rt]==rt)return rt;
	g[rt]=find(g[rt]);
	return g[rt];
}
int main(){
//	freopen("monkey.in","r",stdin);
//	freopen("monkey.out","w",stdout);
	int i,j,k;
	m=read();
	for(i=1;i<=m;i++)monkey[i]=read();
	n=read();
	for(i=1;i<=n;i++){
		x[i]=read();y[i]=read();
		g[i]=i;
	}
	for(i=1;i<=n;i++){
		for(j=1+i;j<=n;j++){
			cnt++;
			d[cnt].s=i;
			d[cnt].t=j;
			d[cnt].data=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
		}
	}
	sort(d+1,d+cnt+1,cmp);
	for(i=1;i<=cnt;i++){
		j=find(d[i].s);
		k=find(d[i].t);
		if(j!=k){
			g[j]=k;
			maxx=max(maxx,d[i].data);
		}
	}
	for(i=1;i<=m;i++){
		if(monkey[i]>=maxx)ans++;
	}
	printf("%d",ans);
	return 0;
}
/*
4
1 2 3 4
6
0 0
1 0
1 2
-1 -1
-2 0
2 2
*/