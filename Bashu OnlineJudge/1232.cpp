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
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int c[1005],n,m,k,p;
int rd1[1000005],rd2[1000005];
int ls1[1000005],ls2[1000005];
struct node{
	int l,r,cnt;
}a[1000005];
int lowbit(int x){
	return (x&(-x));
}
void Add(int x,int y){
	for(int i=x;i<=p;i+=lowbit(i)){
		c[i]+=y;
	}
}
int Ask(int x){
	int ans=0;
	for(int i=x;i>=1;i-=lowbit(i)){
		ans+=c[i];
	}
	return ans;
}
bool cmp(node x,node y){
	if(x.l!=y.l)return x.l>y.l;
	return x.r<y.r;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int T=read();
	for(int lcx=1;lcx<=T;lcx++){
		n=read();m=read();k=read();
		memset(c,0,sizeof(c));
		memset(a,0,sizeof(a));
		memset(rd1,0,sizeof(rd1));
		memset(rd2,0,sizeof(rd2));
		memset(ls1,0,sizeof(ls1));
		memset(ls2,0,sizeof(ls2));
		for(int i=1;i<=k;i++){
			a[i].l=read();
			a[i].r=read();
			p=max(p,a[i].r);
		}
		sort(a+1,a+k+1,cmp);
		for(int i=1;i<=k;i++){
			rd1[i]=rd1[ls1[a[i].l]]+1;
			rd2[i]=rd2[ls2[a[i].r]]+1;
			ls1[a[i].l]=i;
			ls2[a[i].r]=i;
		}
		ll ans=0;
		for(int i=1;i<=k;i++){
			a[i].cnt=Ask(a[i].r);
			if(a[i].l==a[i-1].l&&a[i].r==a[i-1].r)a[i].cnt=a[i-1].cnt;
			ans+=a[i].cnt-(rd1[i]-1)-(rd2[i]-1);
			Add(a[i].r,1);
		}
		printf("Test case %d: %lld\n",lcx,ans);
	}
	return 0;
}