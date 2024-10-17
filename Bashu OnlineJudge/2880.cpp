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
int read(){
	int s=0;char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s;
}
struct edge{
	int s,t,data;
}d[100005];
int n,m,g[100005],ans;
bool cmp(edge x,edge y){
	return x.data<y.data;
}
int find(int rt){
	if(rt==g[rt])return rt;
	g[rt]=find(g[rt]);
	return g[rt];
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	for(i=1;i<=m;i++){
		d[i].s=read();d[i].t=read();d[i].data=read();
	}
	sort(d+1,d+m+1,cmp);
	for(i=1;i<=n;i++){
		g[i]=i;
	}
	for(i=1;i<=m;i++){
		j=find(d[i].s);
		k=find(d[i].t);
		if(j!=k)ans=max(ans,d[i].data);
		g[j]=k;
	}
	printf("%d",ans);
	return 0;
}