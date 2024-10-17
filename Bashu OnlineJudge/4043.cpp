#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1005;
const int M=N*N;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,tot;
double In[N],val[N];
int pre[N],id[N],vis[N],T[N];
struct edge{
	int s,t;
	double data;
}e[M];
double Solve(){
	double ans=0;
	int root=++n;
	while(1){
		//1.找最小入度边 
		for(int i=1;i<=n;i++)In[i]=inf;
		In[root]=0;
		for(int i=1;i<=tot;i++){
			int x=e[i].s,y=e[i].t;
			if(In[y]>e[i].data&&x!=y){
				In[y]=e[i].data;
				pre[y]=x;
			}
		}
		//2.找环 
		cnt=0;
		memset(id,-1,sizeof(id));
		memset(vis,-1,sizeof(vis));
		for(int i=1;i<=n;i++){//标记每个环 
			ans+=In[i];
			int x=i;
			while(vis[x]!=i&&id[x]==-1&&x!=root){//找环 
				vis[x]=i;
				x=pre[x];
			}
			if(x!=root&&id[x]==-1){//环上的编号 
				id[x]=++cnt;
				for(int y=pre[x];x!=y;y=pre[y])id[y]=cnt;
			}
		}
		if(cnt==0)break;//无环 
		for(int i=1;i<=n;i++){
			if(id[i]==-1)id[i]=++cnt;//给剩余孤立点编号 
		}
		//3.缩点 
		for(int i=1;i<=tot;i++){
			int x=e[i].t;
			e[i].s=id[e[i].s];
			e[i].t=id[e[i].t];
			if(e[i].s!=e[i].t)e[i].data-=In[x];
		}
		n=cnt;
		root=id[root];
	}
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	double ans=0;
	for(int i=1;i<=n;i++){
		scanf("%lf",&val[i]);
		e[++tot]=(edge){n+1,i,val[i]};
		T[i]=read();
	}
	m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		double Val;scanf("%lf",&Val);
		e[++tot]=(edge){x,y,Val};
		val[y]=min(val[y],Val);
	}
	for(int i=1;i<=n;i++){
		ans+=(T[i]-1)*val[i];
	}
	ans+=Solve();
	printf("%.2lf",ans);
	return 0;
}