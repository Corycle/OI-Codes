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
const int N=10005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
int h[N],c[N],dis[N],vis[N];
struct edge{int to,next,cost;}d[N*10];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
/*
bool SPFA(int s){
	queue<int>q;q.push(s);dis[s]=0;
	while(q.size()){
		int x=q.front();q.pop();vis[x]=0;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(dis[y]<dis[x]+d[i].cost){
				dis[y]=dis[x]+d[i].cost;
				if((++c[y])>n)return false;
				if(!vis[y]){vis[y]=1;q.push(y);}
			}
		}
	}
	return true;
}
*/
bool SPFA(int x){
	vis[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(dis[y]<dis[x]+d[i].cost){
			dis[y]=dis[x]+d[i].cost;
			if(vis[y]){vis[x]=0;return false;}
			if(!SPFA(y)){vis[x]=0;return false;}
		}
	}
	vis[x]=0;
	return true;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int op=read(),x=read(),y=read();
		if(op==1)Add(y,x,read());
		if(op==2)Add(x,y,-read());
		if(op==3){Add(x,y,0);Add(y,x,0);}
	}
	for(int i=1;i<=n;i++){
		dis[i]=0;
		if(!SPFA(i)){
			printf("No");
			return 0;
		}
	}
	printf("Yes");
	return 0;
}