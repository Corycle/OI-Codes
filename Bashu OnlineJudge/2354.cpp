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
long long read(){
	long long s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
long long n,m,x[1005],y[1005],g[1005],num,cnt;
long double ans;
long long find(long long x){
	if(g[x]==x)return x;
	g[x]=find(g[x]);
	return g[x];
}
struct edge{
	long long s,t;
	long double data;
}d[1000005];
bool cmp(edge a,edge b){
	return a.data<b.data;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	for(i=1;i<=n;i++){
		x[i]=read();
		y[i]=read();
		g[i]=i;
	}
	for(i=1;i<=m;i++){
		j=find(read());k=find(read());
		if(j!=k){
			g[j]=k;
			num++;
		}
	}
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
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
			ans+=d[i].data;
			num++;
		}
		if(num==n-1)break;
	}
	printf("%.2LF",ans);
	return 0;
}