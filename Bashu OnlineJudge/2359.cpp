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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,Max,Min,sum,Ans;
int h[N],dis[N],vis[N];
struct edge{int to,next,w;}d[N*20];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
int gcd(int x,int y){
	return y==0?x:gcd(y,x%y);
}
void DFS(int x,int dep){
	if(dis[x]){
		if(!Ans)Ans=abs(dep-dis[x]);
		else Ans=gcd(Ans,abs(dep-dis[x]));
		return;
	}
	dis[x]=dep;vis[x]=1;
	Max=max(Max,dis[x]);
	Min=min(Min,dis[x]);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		DFS(y,dep+d[i].w);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		Add(x,y,1);Add(y,x,-1);
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			Max=-inf;Min=inf;
			DFS(i,1);
			sum+=Max-Min+1;
		}
	}
	if(Ans){
		if(Ans<3)printf("-1 -1");
		else{
			for(int i=3;i<=Ans;i++){
				if(Ans%i==0){
					printf("%d %d",Ans,i);
					break;
				}
			}
		}
	}
	else{
		if(sum<3)printf("-1 -1");
		else printf("%d 3",sum);
	}
	return 0;
}