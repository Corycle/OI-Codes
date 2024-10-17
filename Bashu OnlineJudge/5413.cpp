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
const double eps=1e-8;
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
double dis[N];
int h[N],vis[N];
struct edge{int to,next,a,b;}d[N*20];
void Add(int x,int y,int a,int b){
	d[++cnt]=(edge){y,h[x],a,b};
	h[x]=cnt;
}
void Prepare(){
	cnt=0;
	memset(h,0,sizeof(h));
	memset(vis,0,sizeof(vis));
	memset(dis,0,sizeof(dis));
}
int BFS(){
	queue<int>q;q.push(1);dis[1]=1;
	while(q.size()){
		int x=q.front();q.pop();
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			double tmp=dis[x]/d[i].a*d[i].b;
			if(!vis[y]){dis[y]=tmp;vis[y]=1;q.push(y);}
			else if(abs(tmp-dis[y])>=eps)return 0;
		}
	}
	return 1;
}
int main(){
//	freopen("gear.in","r",stdin);
//	freopen("gear.out","w",stdout);
	int T=read();
	for(int Case=1;Case<=T;Case++){
		Prepare();
		n=read();m=read();
		for(int i=1;i<=m;i++){
			int x=read(),y=read();
			int a=read(),b=read();
			Add(x,y,a,b);Add(y,x,b,a);
		}
		int ans=BFS();
		printf("Case #%d: ",Case);
		if(ans)printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}