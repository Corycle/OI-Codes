#include<bits/stdc++.h>
using namespace std;
const int inf=0x7fffffff/2;
const int mod=10000;
int n,p,k,ans=-1,q[10005],vis[1005],cnt1,h[1005],d[1005];
struct _{
	int to,next,v;
}a[20005];
void add(int x,int y,int z){
	cnt1++;
	a[cnt1].to=y;
	a[cnt1].v=z;
	a[cnt1].next=h[x];
	h[x]=cnt1;
}
void baihan(){
	int i,j;
	scanf("%d%d%d",&n,&p,&k);
	for(i=1;i<=p;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
		add(y,x,z);
	}
}
void spfa(int u){
	int h1=0,t=1,i;
	for(i=1;i<=n;i++)d[i]=inf,vis[i]=0;
	memset(q,0,sizeof(q));
	d[1]=0;q[1]=1;
	while(h1!=t){
		h1=(h1+1)%mod;
		int x=q[h1];
		vis[x]=0;
		for(i=h[x];i;i=a[i].next){
			int y=a[i].to;
			int va=0;
			if(a[i].v>u)va=1;
			if(d[y]>d[x]+va){
				d[y]=d[x]+va;
				if(!vis[y]){
					t=(t+1)%mod;
					q[t]=y;
					vis[y]=1;
				}
			}
		}
	}
}
void work(){
	int l=0,r=inf,mid;
	while(l<=r){//因为要求最大值的最小，自然想到二分 
		mid=(l+r)/2;
		spfa(mid);
		if(d[n]<=k){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	printf("%d\n",ans);
}
int main(){
	baihan();
	work();
	return 0;
}