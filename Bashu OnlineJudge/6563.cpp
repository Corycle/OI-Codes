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
const int N=1e6+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll L[N],R[N];
int n,m,cnt,flag,h[N];
struct Node{ll l,r;}P[N];
struct edge{int to,next,dist;}d[N*2];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
void DFS(int x,int fa){
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;
		DFS(y,x);
		L[x]=max(L[x],L[y]-d[i].dist);
		R[x]=min(R[x],R[y]+d[i].dist);
	}
	if(L[x]>R[x])flag=0;
}
bool Check(int x){
	for(int i=1;i<=n;i++){
		L[i]=P[i].l-x;
		R[i]=P[i].r+x;
	}
	flag=1;
	DFS(1,0);
	return flag;
}
int main(){
//	freopen("teleport.in","r",stdin);
//	freopen("teleport.out","w",stdout);
	int T=read(),type=read();
	while(T--){
		n=read();
		for(int i=1;i<=n;i++)h[i]=0;cnt=0;
		for(int i=1;i<=n;i++)P[i].l=read();
		for(int i=1;i<=n;i++)P[i].r=read();
		for(int i=1;i<n;i++){
			int x=read(),y=read(),z=read();
			Add(x,y,z);Add(y,x,z);
		}
		int l=0,r=1e9,ans=0;
		while(l<=r){
			int mid=(l+r)>>1;
			if(Check(mid)){
				ans=mid;
				r=mid-1;
			}
			else l=mid+1;
		}
		printf("%d\n",type?ans:(ans>0));
	}
	return 0;
}