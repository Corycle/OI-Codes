#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int M=2000005;
const int N=40005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt=1,Cost,Flow;
int h[N],dis[N],vis[N],pre[N];
int id(int x,int y){return ((x-1)*m+y)*4;}
int U(int x,int y){return ((x-1)*m+y)*4+0;}
int R(int x,int y){return ((x-1)*m+y)*4+1;}
int D(int x,int y){return ((x-1)*m+y)*4+2;}
int L(int x,int y){return ((x-1)*m+y)*4+3;}
struct edge{int to,next,flow,cost;}d[M];
void Add(int x,int y,int f,int c,int s){
	if(s==2)swap(x,y);
	d[++cnt]=(edge){y,h[x],f,c};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0,-c};h[y]=cnt;
}
bool SPFA(int S,int T){
	queue<int>q;
	memset(vis,0,sizeof(vis));
	memset(pre,0,sizeof(pre));
	memset(dis,0x3f,sizeof(dis));
	q.push(S);dis[S]=0;
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
	if(dis[T]<inf)return true;
	return false;
}
void Adjust(int S,int T){
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
	Flow+=dlt;
	Cost+=dis[T]*dlt;
}
void Edmonds_Karp(int S,int T){
	while(SPFA(S,T))Adjust(S,T);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int sum=0;
	n=read();m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int s=(i+j+1)%2+1;
			int x=read(),num=id(i,j);
			sum+=__builtin_popcount(x);
			if((i+j)&1){
				if(i+1<=n)Add(D(i,j),U(i+1,j),1,0,s);
				if(j-1>=1)Add(L(i,j),R(i,j-1),1,0,s);
				if(i-1>=1)Add(U(i,j),D(i-1,j),1,0,s);
				if(j+1<=m)Add(R(i,j),L(i,j+1),1,0,s);
			}
			if(x&1)Add(s,U(i,j),1,0,s);
			if(x&2)Add(s,R(i,j),1,0,s);
			if(x&4)Add(s,D(i,j),1,0,s);
			if(x&8)Add(s,L(i,j),1,0,s);
			
			if(x==1) {Add(U(i,j),L(i,j),1,1,s);Add(U(i,j),R(i,j),1,1,s);Add(U(i,j),D(i,j),1,2,s);}//↑ 
			if(x==2) {Add(R(i,j),U(i,j),1,1,s);Add(R(i,j),D(i,j),1,1,s);Add(R(i,j),L(i,j),1,2,s);}//→ 
			if(x==4) {Add(D(i,j),L(i,j),1,1,s);Add(D(i,j),R(i,j),1,1,s);Add(D(i,j),U(i,j),1,2,s);}//↓ 
			if(x==8) {Add(L(i,j),U(i,j),1,1,s);Add(L(i,j),D(i,j),1,1,s);Add(L(i,j),R(i,j),1,2,s);}//← 
			
			if(x==3) {Add(R(i,j),L(i,j),1,1,s);Add(U(i,j),D(i,j),1,1,s);}//└ 
			if(x==6) {Add(R(i,j),L(i,j),1,1,s);Add(D(i,j),U(i,j),1,1,s);}//┌ 
			if(x==9) {Add(L(i,j),R(i,j),1,1,s);Add(U(i,j),D(i,j),1,1,s);}//┘ 
			if(x==12){Add(L(i,j),R(i,j),1,1,s);Add(D(i,j),U(i,j),1,1,s);}//┐ 
			
			if(x==7) {Add(U(i,j),L(i,j),1,1,s);Add(D(i,j),L(i,j),1,1,s);Add(R(i,j),L(i,j),1,2,s);}//├ 
			if(x==11){Add(L(i,j),D(i,j),1,1,s);Add(R(i,j),D(i,j),1,1,s);Add(U(i,j),D(i,j),1,2,s);}//┴ 
			if(x==13){Add(U(i,j),R(i,j),1,1,s);Add(D(i,j),R(i,j),1,1,s);Add(L(i,j),R(i,j),1,2,s);}//┤ 
			if(x==14){Add(L(i,j),U(i,j),1,1,s);Add(R(i,j),U(i,j),1,1,s);Add(D(i,j),U(i,j),1,2,s);}//┬ 
		}
	}
	Edmonds_Karp(1,2);
	if(2*Flow==sum)printf("%d",Cost);
	else printf("-1");
	return 0;
}