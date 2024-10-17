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
}d[250005];
int n,m,g[505],ans;
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
	n=read();
	for(i=1;i<=n;i++){
		j=read();
		m++;
		d[m].s=0;d[m].t=i;d[m].data=j;
		g[i]=i;
	}
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			k=read();
			if(i<=j)continue;
			m++;
			d[m].s=i;d[m].t=j;d[m].data=k;
		}
	}
	sort(d+1,d+m+1,cmp);
	for(i=1;i<=m;i++){
		j=find(d[i].s);
		k=find(d[i].t);
		if(j!=k)ans+=d[i].data;
		g[j]=k;
	}
	printf("%d",ans);
	return 0;
}
/*
4 
5 
4
4 
3 
0 2 2 2 
2 0 3 3 
2 3 0 4 
2 3 4 0 
*/