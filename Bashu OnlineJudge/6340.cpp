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
const int N=30;
const int n=24;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int cnt,h[N],a[N],b[N],c[N],vis[N],dis[N];
struct edge{int to,next,dist;}d[N*10];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
bool SPFA(){
	memset(c,0,sizeof(c));
	memset(vis,0,sizeof(vis));
	memset(dis,-0x3f,sizeof(dis));
	queue<int>q;q.push(0);dis[0]=0;
	while(!q.empty()){
		int x=q.front();q.pop();vis[x]=0;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(dis[y]<dis[x]+d[i].dist){
				dis[y]=dis[x]+d[i].dist;
				if((++c[y])>n)return false;
				if(!vis[y]){vis[y]=1;q.push(y);}
			}
		}
	}
	return true;
}
bool Check(int sum){
	cnt=0;
	memset(h,0,sizeof(h));
	for(int i=1;i<=8;i++)Add(i+16,i,a[i]-sum);//s[i]-s[i+16]>=a[i]-s[24]
	for(int i=9;i<=n;i++)Add(i-8,i,a[i]);//s[i]-s[i-8]>=a[i]
	for(int i=1;i<=n;i++)Add(i,i-1,-b[i]);//s[i-1]-s[i]>=-b[i]
	for(int i=1;i<=n;i++)Add(i-1,i,0);//s[i]-s[i-1]>=0
	Add(n,0,-sum);//s[0]-s[n]>=-sum
	Add(0,n,sum);//s[n]-s[0]>=sum
	return SPFA();
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		for(int i=1;i<=n;i++)a[i]=read();
		for(int i=1;i<=n;i++)b[i]=read();
		int l=0,r=0,Ans=-1;
		for(int i=1;i<=n;i++)r+=b[i];
		while(l<=r){
			int mid=(l+r)>>1;
			if(Check(mid)){
				Ans=mid;
				r=mid-1;
			}
			else l=mid+1;
		}
		printf("%d\n",Ans);
	}
	return 0;
}