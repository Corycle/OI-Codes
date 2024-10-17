/*
	Name: luogu P3403
	Author: Corycle
*/
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
#define pii pair<ll,int>
#define fst first
#define scd second
#define mp make_pair
using namespace std;
const ll inf=9e18;
const int N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll h,Ans,dis[N];
int a,b,c,vis[N];
priority_queue<pii,vector<pii>,greater<pii> >q;
void Dijkstra(){
	for(int i=0;i<a;i++)dis[i]=inf;
	q.push(mp(1,1));dis[1]=1;
	while(q.size()){
		int x=q.top().scd;q.pop();
		if(vis[x])continue;vis[x]=1;
		if(dis[(x+b)%a]>dis[x]+b){
			dis[(x+b)%a]=dis[x]+b;
			q.push(mp(dis[(x+b)%a],(x+b)%a));
		}
		if(dis[(x+c)%a]>dis[x]+c){
			dis[(x+c)%a]=dis[x]+c;
			q.push(mp(dis[(x+c)%a],(x+c)%a));
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	h=read();a=read();b=read();c=read();
	if(a==1||b==1||c==1){printf("%lld",h);return 0;}
	Dijkstra();
	for(int i=0;i<a;i++){
		if(dis[i]<=h&&dis[i]!=inf)Ans+=(h-dis[i])/a+1;
	}
	printf("%lld",Ans);
	return 0;
}
