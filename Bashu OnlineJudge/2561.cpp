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
const int M=100005;
const int N=5005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
int S,T,tot,ans,cnt=1;
int L[N],R[N],h[N],b[N];
int pre[N],vis[N],dis[N];
struct edge{
	int to,next,flow,cost;
}d[N*20];
void Add(int x,int y,int f,int c){
	d[++cnt]=(edge){y,h[x],f,c};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0,-c};h[y]=cnt;
}
bool SPFA(){
	queue<int>q;
	memset(vis,0,sizeof(vis));
	memset(pre,0,sizeof(pre));
	memset(dis,0x3f,sizeof(dis));
	q.push(S);dis[S]=0;
	while(q.size()){
		int x=q.front();
		q.pop();vis[x]=0;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].flow&&dis[y]>dis[x]+d[i].cost){
				dis[y]=dis[x]+d[i].cost;
				pre[y]=i;
				if(!vis[y]){
					vis[y]=1;
					q.push(y);
				}
			}
		}
	}
	if(dis[T]<inf)return true;
	return false;
}
void Adjust(){
	int p=0,dlt=inf;
	for(int i=T;i!=S;i=d[p^1].to){
		p=pre[i];
		dlt=min(dlt,d[p].flow);
	}
	for(int i=T;i!=S;i=d[p^1].to){
		p=pre[i];
		d[p].flow-=dlt;
		d[p^1].flow+=dlt;
	}
	ans-=dis[T]*dlt;
}
void Edmonds_Karp(){
	while(SPFA())Adjust();
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		b[++tot]=L[i]=read()+M;
		b[++tot]=R[i]=read()+M;
		if(L[i]>R[i])swap(L[i],R[i]);
	}
	sort(b+1,b+tot+1);
	tot=unique(b+1,b+tot+1)-b-1;
	S=0;T=tot+1;
	Add(S,1,m,0);
	for(int i=1;i<=tot;i++){
		Add(i,i+1,inf,0);
	}
	for(int i=1;i<=n;i++){
		int len=R[i]-L[i];
		L[i]=lower_bound(b+1,b+tot+1,L[i])-b;
		R[i]=lower_bound(b+1,b+tot+1,R[i])-b;
		Add(L[i],R[i],1,-len);
	}
	Edmonds_Karp();
	printf("%d",ans);
	return 0;
}