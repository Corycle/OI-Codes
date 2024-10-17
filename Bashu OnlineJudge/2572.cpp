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
int n,m,g[10005],ans;
struct edge{
	int s,t,data;
}d[100005];
bool cmp(edge x,edge y){
	return x.data<y.data;
}
int find(int x){
	return x==g[x]?x:g[x]=find(g[x]);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	for(i=1;i<=m;i++){
		d[i].s=read();
		d[i].t=read();
		d[i].data=read();
	}
	sort(d+1,d+m+1,cmp);
	for(i=1;i<=n;i++)g[i]=i;
	for(i=1;i<=m;i++){
		j=find(d[i].s);
		k=find(d[i].t);
		if(j!=k){
			g[j]=k;
			ans+=d[i].data;
		}
	}
	printf("%d",ans);
	return 0;
}