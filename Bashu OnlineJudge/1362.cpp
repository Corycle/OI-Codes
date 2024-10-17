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
int n,m,g[100005],sum[100005];
long long ans;
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
	int T=read();
	while(T--){
		n=read();
		memset(d,0,sizeof(d));
		memset(g,0,sizeof(g));
		memset(sum,0,sizeof(sum));
		m=0;ans=0;
		for(i=1;i<n;i++){
			d[i].s=read();d[i].t=read();d[i].data=read();
		}
		sort(d+1,d+n,cmp);
		for(i=1;i<=n;i++){
			g[i]=i;
			sum[i]=1;
		}
		for(i=1;i<n;i++){
			j=find(d[i].s);
			k=find(d[i].t);
//			ans+=d[i].data;
			g[j]=k;
			int num=sum[j]*sum[k]-1;
			ans+=(long long)num*(d[i].data+1);
			sum[k]+=sum[j];
		}
		printf("%lld\n",ans);
	}
	
	return 0;
}