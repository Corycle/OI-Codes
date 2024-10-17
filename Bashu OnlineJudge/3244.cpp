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
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
int h[N],vis[N];
double dis[N];
struct edge{
	int to,next;
	double dist;
}d[N*2];
void Add(int x,int y,double z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
struct cmp{
	bool operator()(int x,int y){
		return dis[x]<dis[y];
	}
};
void SPFA(){
	priority_queue<int,vector<int>,cmp>q;
	q.push(1);dis[1]=1;
	while(q.size()){
		int x=q.top();q.pop();vis[x]=0;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(dis[y]<dis[x]*d[i].dist){
				dis[y]=dis[x]*d[i].dist;
				if(!vis[y]){vis[y]=1;q.push(y);}
			}
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		double z=read()/100.0;
		Add(x,y,z);Add(y,x,z);
	}
	SPFA();
	printf("%.6lf",dis[n]*100);
	return 0;
}