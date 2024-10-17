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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,p,tot,ans,f[N],b[N];
struct Tree{int maxx;}t[N*4];
struct node{int x,y,data;}a[N];
bool cmp(node x,node y){
	if(x.x!=y.x)return x.x<y.x;
	return x.y<y.y;
}
void update(int num){
	t[num].maxx=max(t[num<<1].maxx,t[num<<1|1].maxx);
}
void Change(int x,int y,int num,int l,int r){
	if(x<l||x>r)return;
	if(l==r){
		t[num].maxx=y;
		return;
	}
	int mid=(l+r)>>1;
	Change(x,y,lson);
	Change(x,y,rson);
	update(num);
}
int Ask(int x,int y,int num,int l,int r){
	if(y<l||x>r)return 0;
	if(x<=l&&r<=y)return t[num].maxx;
	int mid=(l+r)>>1;
	return max(Ask(x,y,lson),Ask(x,y,rson));
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();p=read();
	for(int i=1;i<=p;i++){
		a[i].x=read();
		a[i].y=read();
		a[i].data=read();
		b[i]=a[i].y;
	}
	sort(b+1,b+p+1);
	sort(a+1,a+p+1,cmp);
	tot=unique(b+1,b+p+1)-b-1;
	for(int i=1;i<=p;i++){
		a[i].y=lower_bound(b+1,b+tot+1,a[i].y)-b;
	}
	for(int i=1;i<=p;i++){
		f[i]=Ask(1,a[i].y,1,1,tot)+a[i].data;
		Change(a[i].y,f[i],1,1,tot);
		ans=max(ans,f[i]);
	}
	printf("%d",ans);
	return 0;
}