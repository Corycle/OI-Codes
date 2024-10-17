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
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot,cnt=1,flag;
struct Point{int x,y;}P[N];
int A[N],b1[N],n1[N],l1[N];
int B[N],b2[N],n2[N],l2[N];
int h[N],H[N],dis[N],pos[N],down[N];
struct edge{int to,next,flow;}d[N*10];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
}
void Addedge(int x,int y,int l,int r){
	if(l>r){puts("-1");exit(0);}
	down[x]-=l;down[y]+=l;Add(x,y,r-l);
}
bool BFS(int s,int t){
	for(int i=1;i<=tot;i++)dis[i]=-1;
	queue<int>q;q.push(s);dis[s]=0;
	while(q.size()){
		int x=q.front();q.pop();
		if(x==t)return true;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].flow&&dis[y]==-1){
				dis[y]=dis[x]+1;q.push(y);
			}
		}
	}
	return false;
}
int DFS(int x,int maxn,int t){
	if(x==t||!maxn)return maxn;
	int ans=0;
	for(int &i=H[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].flow&&dis[y]==dis[x]+1){
			int dlt=DFS(y,min(d[i].flow,maxn),t);
			if(!dlt)dis[y]=-1;
			d[i].flow-=dlt;
			d[i^1].flow+=dlt;
			maxn-=dlt;ans+=dlt;
			if(!maxn)return ans;
		}
	}
	return ans;
}
int Dinic(int s,int t){
	int ans=0;
	while(BFS(s,t)){for(int i=1;i<=tot;i++)H[i]=h[i];ans+=DFS(s,inf,t);}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	int wr=read(),wb=read();
	if(wr>wb){swap(wr,wb);flag=1;}
	for(int i=1;i<=n;i++){
		P[i].x=b1[++b1[0]]=read();
		P[i].y=b2[++b2[0]]=read();
	}
	sort(b1+1,b1+b1[0]+1);b1[0]=unique(b1+1,b1+b1[0]+1)-b1-1;
	sort(b2+1,b2+b2[0]+1);b2[0]=unique(b2+1,b2+b2[0]+1)-b2-1;
	for(int i=1;i<=n;i++){
		P[i].x=lower_bound(b1+1,b1+b1[0]+1,P[i].x)-b1;n1[P[i].x]++;
		P[i].y=lower_bound(b2+1,b2+b2[0]+1,P[i].y)-b2;n2[P[i].y]++;
	}
	for(int i=1;i<=b1[0];i++){A[i]=++tot;l1[i]=n1[i];}
	for(int i=1;i<=b2[0];i++){B[i]=++tot;l2[i]=n2[i];}
	for(int i=1;i<=m;i++){
		int op=read(),x=read(),d=read();
		if(op==1){int p=lower_bound(b1+1,b1+b1[0]+1,x)-b1;if(b1[p]!=x)continue;l1[p]=min(l1[p],d);}
		if(op==2){int p=lower_bound(b2+1,b2+b2[0]+1,x)-b2;if(b2[p]!=x)continue;l2[p]=min(l2[p],d);}
	}
	int s=++tot,t=++tot;
	for(int i=1;i<=n;i++){Add(A[P[i].x],B[P[i].y],1);pos[i]=cnt;}
	for(int i=1;i<=b1[0];i++)Addedge(s,A[i],(int)(ceil((n1[i]-l1[i])/2.0)),(int)(floor((n1[i]+l1[i])/2.0)));
	for(int i=1;i<=b2[0];i++)Addedge(B[i],t,(int)(ceil((n2[i]-l2[i])/2.0)),(int)(floor((n2[i]+l2[i])/2.0)));
	int S=++tot,T=++tot,sum=0;
	for(int i=1;i<S;i++){
		if(down[i]>0){Add(S,i,down[i]);sum+=down[i];}
		if(down[i]<0)Add(i,T,-down[i]);
	}
	Add(t,s,inf);
	int tmp=Dinic(S,T);
	if(tmp!=sum){puts("-1");return 0;}
	int num=Dinic(s,t);
	printf("%lld\n",1ll*wr*num+1ll*wb*(n-num));
	for(int i=1;i<=n;i++)printf("%c",(d[pos[i]].flow!=flag?'r':'b'));
	return 0;
}
