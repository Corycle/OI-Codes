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
#define ld long double
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
const int M=105;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[M];
ll n,m;
ld L,P,a[N],sum[N],f[N];
struct node{
	ll l,r,p;
}q[N];
ld Pow(ld x,ll y){
	ld ans=1,tot=x;
	while(y){
		if(y&1)ans=ans*tot;
		tot*=tot;
		y/=2;
	}
	return ans;
}
ld Val(ll j,ll i){
	ld x=(sum[i]-sum[j])+(i-j-1)-L;
	return f[j]+Pow(abs(x),P);
}
ll Find(ll p1,ll p2,ll l,ll r){
	ll ans=r+1;
	while(l<=r){
		ll mid=(l+r)>>1;
		if(Val(p1,mid)<=Val(p2,mid)){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int Case=read();
	while(Case--){
		n=read();L=read();P=read();
		for(int i=1;i<=n;i++){
			scanf("%s",s+1);
			a[i]=strlen(s+1);
			sum[i]=sum[i-1]+a[i];
		}
		int l=1,r=1;
		q[1]=(node){0,n,0};
		for(ll i=1;i<=n;i++){
			while(l<=r&&q[l].r<i)l++;
			f[i]=Val(q[l].p,i);
			if(l>r||Val(i,n)<=Val(q[r].p,n)){
				while(l<=r&&Val(i,q[r].l)<=Val(q[r].p,q[r].l))r--;
				if(l>r)q[++r]=(node){i,n,i};
				else{
					ll t=Find(i,q[r].p,q[r].l,q[r].r);
					q[r].r=t-1;
					q[++r]=(node){t,n,i};
				}
			}
		}
		if(f[n]<=1e18)printf("%.0LF\n",f[n]);
		else printf("Too hard to arrange\n");
	}
	return 0;
}