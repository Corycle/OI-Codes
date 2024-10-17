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
const int N=500005;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline ll read(){
	ll s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
ll m,sum[N];
int n,a[N],b[N];
ll Calc(int l,int r,int ls,int rs){
	if(l==r)return rs-ls;
	return sum[r-1]-sum[l-1]-ls+rs;
}
bool Check(int Need){
	ll T=0;
	int ls=0,rs=0,l=1,r=1;
	for(int i=1;i<=n;i++){
		if(Need>=b[i]){
			T+=1ll*b[i]*(a[i]-a[1]);
			Need-=b[i];
		}
		else{
			T+=1ll*Need*(a[i]-a[1]);
			rs=Need;Need=0;r=i;
			break;
		}
	}
	if(T<=m)return true;
	for(int i=2;i<=n;i++){
		T-=Calc(i,r,0,rs)*(a[i]-a[i-1]);
		T+=Calc(l,i-1,ls,b[i-1])*(a[i]-a[i-1]);
		while(r<=n&&(a[r]-a[i])<(a[i]-a[l])){
			int res=min(b[l]-ls,b[r]-rs);
			T-=1ll*res*(a[i]-a[l]);
			T+=1ll*res*(a[r]-a[i]);
			ls+=res;rs+=res;
			if(ls>=b[l]){l++;ls=0;}
			if(rs>=b[r]){r++;rs=0;}
		}
		if(T<=m)return true;
	}
	return false;
}
int main(){
//	freopen("block.in","r",stdin);
//	freopen("block.out","w",stdout);
	n=read();m=read()/2;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+b[i];
	ll l=0,r=sum[n],ans=0;
	while(l<=r){
		ll mid=(l+r)>>1;
		if(Check(mid)){
			ans=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	printf("%lld",ans);
	return 0;
}