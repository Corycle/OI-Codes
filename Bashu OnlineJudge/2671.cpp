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
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
struct edge{
	int s,t;
	double data;
	bool vis;
}d[250005];
int n,m,g[505],num,f[505],line[505];
double x[505],y[505];
int find(int rt){
	if(rt==g[rt])return rt;
	g[rt]=find(g[rt]);
	return g[rt];
}
bool cmp1(edge a,edge b){
	return a.data<b.data;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	num=read();n=read();
	for(i=1;i<=n;i++){
		x[i]=read();y[i]=read();
		g[i]=i;
	}
	for(i=1;i<n;i++){
		for(j=i+1;j<=n;j++){
			m++;
			d[m].s=i;d[m].t=j;
			d[m].data=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
		}
	}
	sort(d+1,d+m+1,cmp1);
	int l=0;
	for(i=1;i<=m;i++){
		j=find(d[i].s);
		k=find(d[i].t);
		if(j!=k){
			d[i].vis=true;
			g[j]=k;
			l++;
            line[l]=i;
		}
		if(l==n-1)break;
	}
	if(num==0)num=1;
	printf("%.2lf",d[line[n-num]].data);
	return 0;
}