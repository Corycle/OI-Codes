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
const ll inf=9e18;
const ll tmp=1e10;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,W,P,Q,cnt;
int h[N],A[N],H[N],dis[N];
struct edge{int to,next;ll flow;}d[N*10];
void Add(int x,int y,ll z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
}
bool BFS(int s,int t){
	for(int i=1;i<=t;i++)dis[i]=-1;
	queue<int>q;q.push(s);dis[s]=0;
	while(q.size()){
		int x=q.front();q.pop();
		if(x==t)return true;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].flow&&dis[y]==-1){
				dis[y]=dis[x]+1;
				q.push(y);
			}
		}
	}
	return false;
}
ll DFS(int x,ll maxx,int t){
	if(x==t||!maxx)return maxx;
	ll ans=0;
	for(int &i=H[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].flow&&dis[y]==dis[x]+1){
			ll dlt=DFS(y,min(maxx,d[i].flow),t);
			if(!dlt)dis[y]=-1;
			d[i].flow-=dlt;
			d[i^1].flow+=dlt;
			ans+=dlt;maxx-=dlt;
			if(!maxx)return ans;
		}
	}
	return ans;
}
ll Dinic(int s,int t){
	ll ans=0;
	while(BFS(s,t)){
		for(int i=1;i<=t;i++)H[i]=h[i];
		ans+=DFS(s,inf,t);
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int Case=read();
	while(Case--){
		n=read();W=read();P=read();Q=read();
		int S=n+1,T=n+2;cnt=1;
		for(int i=1;i<=T;i++)h[i]=A[i]=0;
		for(int i=1;i<=P;i++){
			int x=read(),y=read(),z=read();
			int a=read(),b=read(),c=read();
			int d=read(),e=read(),f=read();
			A[x]+=d-f;A[y]+=e-d;A[z]+=f-e;
			Add(x,y,a*2);Add(y,x,a*2);
			Add(y,z,b*2);Add(z,y,b*2);
			Add(z,x,c*2);Add(x,z,c*2);
		}
		for(int i=1;i<=Q;i++){
			int x=read(),y=read(),t=read();
			if(t==0)Add(y,x,inf);
			if(t==1){Add(x,y,inf);Add(y,x,inf);}
			if(t==2){Add(S,x,inf);Add(y,T,inf);}
		}
		for(int i=1;i<=n;i++){
			Add(S,i,tmp+(A[i]+1));
			Add(i,T,tmp-(A[i]+1));
		}
		printf("%lld\n",(Dinic(S,T)-n*tmp)*W);
	}
	return 0;
}