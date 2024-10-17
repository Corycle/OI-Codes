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
const int N=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt=1;
int h[N],dis[N],Gap[N];
struct edge{
	int to,next,data;
}d[N*N];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
int DFS(int x,int maxx,int s,int t){
	int ans=0;
	if(x==t)return maxx;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].data&&dis[x]==dis[y]+1){
			int dlt=DFS(y,min(maxx,d[i].data),s,t);
			d[i].data-=dlt;
			d[i^1].data+=dlt;
			ans+=dlt;maxx-=dlt;
			if(dis[s]==n||!maxx)return ans;
		}
	}
	if(!(--Gap[dis[x]]))dis[s]=n;
	Gap[++dis[x]]++;
	return ans;
}
int SAP(int s,int t){
	Gap[0]=n;
	int ans=0;
	while(dis[s]<n)ans+=DFS(s,inf,s,t);
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	
	return 0;
}
