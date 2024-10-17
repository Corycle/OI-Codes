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
const int M=350;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll a[N],sum[N];
int n,m,num,st[N],ed[N],pos[N],vis[N];
void Prepare(){
	while(ed[num]!=n){num++;st[num]=ed[num-1]+1;ed[num]=min(ed[num-1]+M,n);}
	for(int i=1;i<=num;i++)for(int j=st[i];j<=ed[i];j++){pos[j]=i;sum[i]+=a[j];}
}
void update(int x){
	vis[x]=1;
	for(int i=st[x];i<=ed[x];i++){sum[x]-=a[i];a[i]=sqrt(a[i]);sum[x]+=a[i];vis[x]&=(a[i]==1);}
}
void Update(int l,int r){
	int x=pos[l],y=pos[r];
	if(x==y)for(int i=l;i<=r;i++){sum[pos[i]]-=a[i];a[i]=sqrt(a[i]);sum[pos[i]]+=a[i];}
	else{
		for(int i=l;i<=ed[x];i++){sum[pos[i]]-=a[i];a[i]=sqrt(a[i]);sum[pos[i]]+=a[i];}
		for(int i=st[y];i<=r;i++){sum[pos[i]]-=a[i];a[i]=sqrt(a[i]);sum[pos[i]]+=a[i];}
		for(int i=x+1;i<=y-1;i++)if(!vis[i])update(i);
	}
}
ll Query(int l,int r){
	ll ans=0;
	int x=pos[l],y=pos[r];
	if(x==y)for(int i=l;i<=r;i++)ans+=a[i];
	else{
		for(int i=l;i<=ed[x];i++)ans+=a[i];
		for(int i=st[y];i<=r;i++)ans+=a[i];
		for(int i=x+1;i<=y-1;i++)ans+=sum[i];
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	Prepare();
	m=read();
	while(m--){
		int op=read(),l=read(),r=read();
		if(l>r)swap(l,r);
		if(op==0)Update(l,r);
		if(op==1)printf("%lld\n",Query(l,r));
	}
	return 0;
}