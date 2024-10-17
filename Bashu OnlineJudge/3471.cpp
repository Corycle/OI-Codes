#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=2000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,ans,v[N],f[N];
struct Node{ll x,s;}a[N],b[N];
bool cmp1(Node x,Node y){return x.x<y.x;}
bool cmp2(Node x,Node y){return x.x>y.x;}
void DFS(ll l,ll r,ll sum,ll sta,Node c[]){
	if(l>r){
		c[0].x++;
		c[c[0].x].x=sum;
		c[c[0].x].s=sta;
		return;
	}
	DFS(l+1,r,sum,sta,c);
	DFS(l+1,r,sum+v[l],sta|(1<<(l-1)),c);
	DFS(l+1,r,sum-v[l],sta|(1<<(l-1)),c);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++)v[i]=read();
	ll mid=n>>1;
	DFS(1,mid,0,0,a);
	DFS(mid+1,n,0,0,b);
	sort(a+1,a+a[0].x+1,cmp1);
	sort(b+1,b+b[0].x+1,cmp2);
	ll L=1,R=1;
	while(L<=a[0].x&&R<=b[0].x){
		ll pos=R;
		while(R<=b[0].x&&a[L].x+b[R].x>=0){
			if(a[L].x+b[R].x==0&&!f[a[L].s|b[R].s]){
				ans++;f[a[L].s|b[R].s]=1;//判重 
			}
			R++;
		}
		if(L!=a[0].x&&a[L+1].x==a[L].x)R=pos;
		L++;
	}
	printf("%lld",ans-1);
	return 0;
}