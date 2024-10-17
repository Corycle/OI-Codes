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
const int N=5005;
const int M=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,s,t,cnt1,cnt2;
int vis[N],h1[N],h2[N];
double dis[N],sum;
struct edge{
	int to,next;
	double data;
}d1[M],d2[M];
struct node{
	int x;
	double g,f;
};
void Add1(int x,int y,double z){
	d1[++cnt1]=(edge){y,h1[x],z};
	h1[x]=cnt1;
}
void Add2(int x,int y,double z){
	d2[++cnt2]=(edge){y,h2[x],z};
	h2[x]=cnt2;
}
bool operator<(node x,node y){
	return x.f>y.f;
}
void SPFA(){
	queue<int>q;
	for(int i=1;i<=n;i++)dis[i]=inf;
	q.push(t);dis[t]=0;
	while(q.size()){
		int x=q.front();
		q.pop();vis[x]=0;
		for(int i=h2[x];i;i=d2[i].next){
			int y=d2[i].to;
			if(dis[y]>dis[x]+d2[i].data){
				dis[y]=dis[x]+d2[i].data;
				if(!vis[y]){
					vis[y]=1;
					q.push(y);
				}
			}
		}
	}
}
void A_star(){
	priority_queue<node>q;
	q.push((node){s,0,dis[s]});
	while(q.size()){
		node x=q.top();
		q.pop();
		if(x.x==t){
			if(sum-x.g<0){
				printf("%d",cnt);
				return;
			}
			cnt++;
			sum-=x.g;
		}
		for(int i=h1[x.x];i;i=d1[i].next){
			node y;
			y.x=d1[i].to;
			y.g=x.g+d1[i].data;
			y.f=y.g+dis[y.x];
			q.push(y);
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	scanf("%lf",&sum);
	s=1;t=n;
	for(int i=1;i<=m;i++){
		double z;
		int x=read(),y=read();
		scanf("%lf",&z);
		Add1(x,y,z);
		Add2(y,x,z);
	}
	SPFA();
	A_star();
	return 0;
}