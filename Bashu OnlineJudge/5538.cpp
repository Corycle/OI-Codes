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
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=500005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,a[N],fa[N];
int sum[N],cnt[N],ans[N];
struct Tree{
	int minn,bj;
}t[N*4];
bool cmp(int x,int y){
	return x>y;
}
void Pushup(int p){
	t[p].minn=min(t[p<<1].minn,t[p<<1|1].minn);
}
void Pushdown(int p){
	if(t[p].bj){
		t[p<<1].bj+=t[p].bj;
		t[p<<1|1].bj+=t[p].bj;
		t[p<<1].minn+=t[p].bj;
		t[p<<1|1].minn+=t[p].bj;
		t[p].bj=0;
	}
}
void Build(int p,int l,int r){
	if(l==r){
		t[p].minn=l;
		return;
	}
	int mid=(l+r)>>1;
	Build(lson);
	Build(rson);
	Pushup(p);
}
void Add(int x,int y,int z,int p,int l,int r){
	if(y<l||x>r)return;
	if(x<=l&&r<=y){
		t[p].bj+=z;
		t[p].minn+=z;
		return;
	}
	Pushdown(p);
	int mid=(l+r)>>1;
	Add(x,y,z,lson);
	Add(x,y,z,rson);
	Pushup(p);
}
int Ask(int k,int p,int l,int r){
	if(l==r){
		return l+(t[p].minn<k);
	}
	Pushdown(p);
	int mid=(l+r)>>1;
	if(k>t[p<<1|1].minn)return Ask(k,rson);
	else return Ask(k,lson);
}
int main(){
//	freopen("iiidx.in","r",stdin);
//	freopen("iiidx.out","w",stdout);
	double k=0;
	scanf("%d%lf",&n,&k);
	for(int i=1;i<=n;i++){
		sum[i]=1;
		a[i]=read();
	}
	sort(a+1,a+n+1,cmp);
	for(int i=n;i>=1;i--){
		sum[fa[i]=(int)(i/k)]+=sum[i];
		if(a[i]==a[i+1])cnt[i]=cnt[i+1]+1;
	}
	Build(1,1,n);
	for(int i=1;i<=n;i++){
		if(fa[i]&&fa[i]!=fa[i-1]){
			Add(ans[fa[i]],n,sum[fa[i]]-1,1,1,n);
		}
		int x=Ask(sum[i],1,1,n);
		x+=cnt[x];cnt[x]++;
		x-=cnt[x]-1;ans[i]=x;
		Add(x,n,-sum[i],1,1,n);
		printf("%d ",a[ans[i]]);
	}
	return 0;
}