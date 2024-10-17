/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=5005;
const int M=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char a[M][M];
int Case,n,m,A,B,Ans,tot,cnt=1;
int h[N],dis[N],vis[N],pre[N],id[M][M][3];
struct edge{int to,next,flow,cost;}d[N*20];
void Add(int x,int y,int f,int c){
	d[++cnt]=(edge){y,h[x],f,c};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0,-c};h[y]=cnt;
}
bool SPFA(int s,int t){
	for(int i=1;i<=tot;i++){dis[i]=inf;vis[i]=pre[i]=0;}
	queue<int>q;q.push(s);dis[s]=0;
	while(q.size()){
		int x=q.front();q.pop();vis[x]=0;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].flow&&dis[y]>dis[x]+d[i].cost){
				dis[y]=dis[x]+d[i].cost;pre[y]=i;
				if(!vis[y]){vis[y]=1;q.push(y);}
			}
		}
	}
	return (dis[t]!=inf);
}
void Adjust(int s,int t){
	int dlt=inf;
	for(int i=t;i!=s;i=d[pre[i]^1].to){
		int p=pre[i];
		dlt=min(dlt,d[p].flow);
	}
	for(int i=t;i!=s;i=d[pre[i]^1].to){
		int p=pre[i];
		d[p].flow-=dlt;
		d[p^1].flow+=dlt;
	}
	Ans+=dlt*dis[t];
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	Case=read();n=read();m=read();A=read();B=read();
	for(int i=1;i<=n;i++){
		scanf("%s",a[i]+1);
		for(int j=1;j<=m;j++){
			if(a[i][j]=='1')continue;
			id[i][j][0]=++tot;
			id[i][j][1]=++tot;
			id[i][j][2]=++tot;
		}
	}
	int S=++tot,T=++tot;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]=='1')continue;
			if((i+j)&1){
				Add(S,id[i][j][0],1,A*0);
				Add(S,id[i][j][0],1,A*1);
				Add(S,id[i][j][0],1,A*2);
				Add(S,id[i][j][0],1,A*3);
				Add(id[i][j][0],id[i][j][1],1,0);
				Add(id[i][j][0],id[i][j][2],1,0);
				Add(id[i][j][0],id[i][j][1],1,B-A);
				Add(id[i][j][0],id[i][j][2],1,B-A);
				if(i!=1)Add(id[i][j][1],id[i-1][j][1],1,0);
				if(i!=n)Add(id[i][j][1],id[i+1][j][1],1,0);
				if(j!=1)Add(id[i][j][2],id[i][j-1][2],1,0);
				if(j!=m)Add(id[i][j][2],id[i][j+1][2],1,0);
			}
			else{
				Add(id[i][j][0],T,1,A*0);
				Add(id[i][j][0],T,1,A*1);
				Add(id[i][j][0],T,1,A*2);
				Add(id[i][j][0],T,1,A*3);
				Add(id[i][j][1],id[i][j][0],1,0);
				Add(id[i][j][2],id[i][j][0],1,0);
				Add(id[i][j][1],id[i][j][0],1,B-A);
				Add(id[i][j][2],id[i][j][0],1,B-A);
			}
		}
	}
	int q=read();
	for(int i=1;i<=q;i++){
		if(SPFA(S,T))Adjust(S,T);
		if(Case>=8&&Case<=12)printf("%d\n",(Ans>0));
		else printf("%d\n",Ans);
	}
	return 0;
}